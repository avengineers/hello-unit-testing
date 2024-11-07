#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include"power_manager.h"
}

#include "mockup_components_power_manager.h"

#define ADC_MIN_VOLTAGE   0x17FU

TEST(PowerManagerTest, Initialisation)
{
    /* Arrange */
    PowerManagerInit();

    /* Act */
    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, INITIALISATION);
}

TEST(PowerManagerTest, InitialisationFailed)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_UNINITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));

    /* Act */
    powerManagerCyclic();
    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}


TEST(PowerManagerTest, InitialisationPassed)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));

    /* Act */
    powerManagerCyclic();
    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, ACTIVE);
}

TEST(PowerManagerTest, ActiveShutDown)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));

    /* Act */
    powerManagerCyclic();

    shutDown();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}

TEST(PowerManagerTest, ActiveNoCommunication)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillOnce(Return(NO_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, IDLE);
}

TEST(PowerManagerTest, IdleFullCommunication)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillOnce(Return(NO_COMMUNICATION)).WillOnce(Return(FULL_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, ACTIVE);
}

TEST(PowerManagerTest, IdleLowVoltage)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillRepeatedly(Return(NO_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();

    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE - 1), Return(ADC_READ_OK)));
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}

TEST(PowerManagerTest, LowPowerWaiting)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillRepeatedly(Return(NO_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, IDLE);
}

TEST(PowerManagerTest, EnterLowPower)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillRepeatedly(Return(NO_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, LOW_POWER);
}

TEST(PowerManagerTest, LowPowerFullCommunication)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillRepeatedly(Return(NO_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();

    EXPECT_CALL(myMock, getCommunicationStatus()).WillRepeatedly(Return(FULL_COMMUNICATION));
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, ACTIVE);
}

TEST(PowerManagerTest, LowPowerShutdown)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));
    EXPECT_CALL(myMock, getCommunicationStatus()).WillRepeatedly(Return(NO_COMMUNICATION));

    /* Act */
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();
    powerManagerCyclic();

    shutDown();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}

TEST(PowerManagerTest, ADCError)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_NOK)));

    /* Act */
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}

TEST(PowerManagerTest, StayingInPrepareShutdown)
{
    /* Arrange */
    PowerManagerInit();

    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getNetworkControllerStatus()).WillOnce(Return(NETWORK_INITIALIZED));
    EXPECT_CALL(myMock, getADCValue(_)).WillRepeatedly(DoAll(SetArgPointee<0>(ADC_MIN_VOLTAGE), Return(ADC_READ_OK)));

    /* Act */
    powerManagerCyclic();

    shutDown();
    powerManagerCyclic();
    powerManagerCyclic();

    PowerManagerState current_state = getCurrentState();

    /* Assert */
    EXPECT_EQ(current_state, PREPARE_SHUTDOWN);
}
