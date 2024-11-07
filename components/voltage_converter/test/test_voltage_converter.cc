#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "voltage_converter.h"
}

#include "mockup_components_voltage_converter.h"

#define MAX_ADC         0xFFFU
#define MAX_VOLTAGE     16.0f
#define ABS_ERROR       4e-3f   // One step is 16.0/0xFFFU = 0.0039...

class VoltageConverterTest : public Test
{
protected:
    void SetUp(void) override
    {
        voltageConverterInit();
    }
};

TEST_F(VoltageConverterTest, Initialization)
{
    /* Arrange */

    /* Act */
    float voltage = getVoltage();

    /* Assert */
    EXPECT_NEAR(voltage, 0.0f, ABS_ERROR);
}

TEST_F(VoltageConverterTest, Zero)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(0U), Return(ADC_READ_OK)));

    /* Act */
    voltageConverterCyclic();

    /* Assert */
    float voltage = getVoltage();
    EXPECT_NEAR(voltage, 0.0f, ABS_ERROR);
}

TEST_F(VoltageConverterTest, FullRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(MAX_ADC), Return(ADC_READ_OK)));

    /* Act */
    voltageConverterCyclic();

    /* Assert */
    float voltage = getVoltage();
    EXPECT_NEAR(voltage, MAX_VOLTAGE, ABS_ERROR);
}

TEST_F(VoltageConverterTest, HalfRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(1).WillOnce(DoAll(SetArgPointee<0>(MAX_ADC / 2), Return(ADC_READ_OK)));

    /* Act */
    voltageConverterCyclic();

    /* Assert */
    float voltage = getVoltage();
    EXPECT_NEAR(voltage, MAX_VOLTAGE / 2.0f, ABS_ERROR);
}

TEST_F(VoltageConverterTest, ADCReadingError)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getADCValue(_)).Times(2).WillOnce(DoAll(SetArgPointee<0>(MAX_ADC), Return(ADC_READ_OK))).WillOnce(DoAll(SetArgPointee<0>(MAX_ADC / 2), Return(ADC_READ_NOK)));

    /* Act */
    voltageConverterCyclic();
    voltageConverterCyclic();

    /* Assert */
    float voltage = getVoltage();
    EXPECT_NEAR(voltage, MAX_VOLTAGE, ABS_ERROR);
}
