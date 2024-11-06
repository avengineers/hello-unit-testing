#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "diagnostic.h"
}

#include "mockup_components_diagnostic.h"

class DiagnosticTest : public Test
{
protected:
    void SetUp(void) override
    {
        diagnosticInit();
    }
};

TEST_F(DiagnosticTest, Initialization)
{
    /* Arrange */

    /* Act */

    /* Assert */
    EXPECT_FALSE(isDTCSet(HIGH_BEAM_DTC));
    EXPECT_FALSE(isDTCSet(LOW_BEAM_DTC));
}

TEST_F(DiagnosticTest, DebounceOnceBothBeams)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, runDiagnosticTest(HIGH_BEAM)).Times(1).WillOnce(Return(TEST_FAILED));
    EXPECT_CALL(myMock, runDiagnosticTest(LOW_BEAM)).Times(1).WillOnce(Return(TEST_FAILED));

    /* Act */
    diagnosticCyclic();

    /* Assert */
    EXPECT_FALSE(isDTCSet(HIGH_BEAM_DTC));
    EXPECT_FALSE(isDTCSet(LOW_BEAM_DTC));
}

TEST_F(DiagnosticTest, DebounceTwiceBothBeams)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, runDiagnosticTest(_)).Times(4).WillRepeatedly(Return(TEST_FAILED));

    /* Act */
    diagnosticCyclic();
    diagnosticCyclic();

    /* Assert */
    EXPECT_TRUE(isDTCSet(HIGH_BEAM_DTC));
    EXPECT_TRUE(isDTCSet(LOW_BEAM_DTC));
}

TEST_F(DiagnosticTest, DebounceThreeTimesBothBeams)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, runDiagnosticTest(HIGH_BEAM)).Times(3).WillRepeatedly(Return(TEST_FAILED));
    EXPECT_CALL(myMock, runDiagnosticTest(LOW_BEAM)).Times(3).WillRepeatedly(Return(TEST_FAILED));

    /* Act */
    diagnosticCyclic();
    diagnosticCyclic();
    diagnosticCyclic();

    /* Assert */
    EXPECT_TRUE(isDTCSet(HIGH_BEAM_DTC));
    EXPECT_TRUE(isDTCSet(LOW_BEAM_DTC));
}

TEST_F(DiagnosticTest, DebounceWithPass)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, runDiagnosticTest(HIGH_BEAM)).Times(3).WillOnce(Return(TEST_PASSED)).WillRepeatedly(Return(TEST_FAILED));
    EXPECT_CALL(myMock, runDiagnosticTest(LOW_BEAM)).Times(3).WillOnce(Return(TEST_FAILED)).WillOnce(Return(TEST_PASSED)).WillOnce(Return(TEST_FAILED));

    /* Act */
    diagnosticCyclic();
    diagnosticCyclic();
    diagnosticCyclic();

    /* Assert */
    EXPECT_TRUE(isDTCSet(HIGH_BEAM_DTC));
    EXPECT_FALSE(isDTCSet(LOW_BEAM_DTC));
}
