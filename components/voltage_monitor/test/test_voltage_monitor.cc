#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "voltage_monitor.h"
}

#include "mockup_components_voltage_monitor.h"

#define MAX_ADC     0x3FFU
#define ADC_14V     0x37fU
#define ADC_12V     0x2FFU
#define ADC_10V     0x280U
#define MAX_VOLTAGE 16000U
#define VOLTAGE_14V 13998U
#define VOLTAGE_10V 10009U

class VoltageMonitorTest : public Test
{
protected:
    void SetUp(void) override
    {
        voltageMonitorInit();
    }
};

TEST_F(VoltageMonitorTest, VoltageInterface)
{
    /* Arrange */

    /* Act */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);

    /* Assert */
    EXPECT_EQ(voltage, 0U);
    EXPECT_EQ(voltage_status, NOT_VALID);
}

TEST_F(VoltageMonitorTest, NoVoltage)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(0U), Return(ADC_READ_OK)));

    /* Act */
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage, 0U);
    EXPECT_EQ(voltage_status, LOW_VOLTAGE);
}


TEST_F(VoltageMonitorTest, MaxVoltage)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(MAX_ADC), Return(ADC_READ_OK)));

    /* Act */
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage, MAX_VOLTAGE);
    EXPECT_EQ(voltage_status, HIGH_VOLTAGE);
}

TEST_F(VoltageMonitorTest, NormalVoltageHighBorder)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(ADC_14V), Return(ADC_READ_OK)));

    /* Act */
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage, VOLTAGE_14V);
    EXPECT_EQ(voltage_status, NORMAL_VOLTAGE);
}

TEST_F(VoltageMonitorTest, NormalVoltageLowBorder)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(ADC_10V), Return(ADC_READ_OK)));

    /* Act */
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage, VOLTAGE_10V);
    EXPECT_EQ(voltage_status, NORMAL_VOLTAGE);
}

TEST_F(VoltageMonitorTest, VoltageAboveHighBorder)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(ADC_14V + 1U), Return(ADC_READ_OK)));

    /* Act */
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage_status, HIGH_VOLTAGE);
}

TEST_F(VoltageMonitorTest, VoltageBelowLowBorder)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(ADC_10V - 1U), Return(ADC_READ_OK)));

    /* Act */
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage_status, LOW_VOLTAGE);
}

TEST_F(VoltageMonitorTest, ADCError)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(2).WillOnce(DoAll(SetArgPointee<0>(ADC_10V), Return(ADC_READ_OK))).WillOnce(DoAll(SetArgPointee<0>(ADC_10V), Return(ADC_READ_NOK)));

    /* Act */
    voltageMonitorCyclic();
    voltageMonitorCyclic();

    /* Assert */
    uint16_t voltage = 0xFFFFU;
    VoltageStatus voltage_status = getVoltage(&voltage);
    EXPECT_EQ(voltage_status, NOT_VALID);
}
