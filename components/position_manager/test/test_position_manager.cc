#include <gtest/gtest.h>
using namespace testing;

extern "C"
{
#include "position_manager.h"
}

#include "mockup_components_position_manager.h"

#define MOVEMENT_IN_RANGE_FOR_MIDDLE             400U
#define MOVEMENT_OUT_OF_RANGE_FOR_MIDDLE         501U
#define MAX_X                                    1000U
#define MAX_Y                                    1000U

MATCHER_P(PositionEq, expected, "")
{
    return ((arg.x == expected.x) && (arg.y == expected.y));
}

const Position middle = { MAX_X / 2, MAX_Y / 2 };
const Position out_of_range = { 2 * MAX_X , 2 * MAX_Y };
const Position move_left_from_middle = { (MAX_X / 2) - MOVEMENT_IN_RANGE_FOR_MIDDLE, MAX_Y / 2 };
const Position move_right_from_middle = { (MAX_X / 2) + MOVEMENT_IN_RANGE_FOR_MIDDLE, MAX_Y / 2 };
const Position move_up_from_middle = { MAX_X / 2, (MAX_Y / 2) - MOVEMENT_IN_RANGE_FOR_MIDDLE };
const Position move_down_from_middle = { MAX_X / 2, (MAX_Y / 2) + MOVEMENT_IN_RANGE_FOR_MIDDLE };

TEST(PositionManagerTest, MoveLeftInRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(Pointee(PositionEq(move_left_from_middle)))).Times(1);

    /* Act */
    MovementStatus status = moveLeft(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_OK);
}

TEST(PositionManagerTest, MoveLeftOutOfRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveLeft(MOVEMENT_OUT_OF_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_NOT_POSSIBLE);
}

TEST(PositionManagerTest, MoveLeftWrongPosition)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(out_of_range));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveLeft(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, POSITION_WRONG);
}

TEST(PositionManagerTest, MoveRightInRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(Pointee(PositionEq(move_right_from_middle)))).Times(1);

    /* Act */
    MovementStatus status = moveRight(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_OK);
}

TEST(PositionManagerTest, MoveRightOutOfRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveRight(MOVEMENT_OUT_OF_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_NOT_POSSIBLE);
}

TEST(PositionManagerTest, MoveRightWrongPosition)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(out_of_range));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveRight(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, POSITION_WRONG);
}

TEST(PositionManagerTest, MoveUpInRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(Pointee(PositionEq(move_up_from_middle)))).Times(1);

    /* Act */
    MovementStatus status = moveUp(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_OK);
}

TEST(PositionManagerTest, MoveUpOutOfRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveUp(MOVEMENT_OUT_OF_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_NOT_POSSIBLE);
}

TEST(PositionManagerTest, MoveUpWrongPosition)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(out_of_range));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveUp(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, POSITION_WRONG);
}

TEST(PositionManagerTest, MoveDownInRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(Pointee(PositionEq(move_down_from_middle)))).Times(1);

    /* Act */
    MovementStatus status = moveDown(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_OK);
}

TEST(PositionManagerTest, MoveDownOutOfRange)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(middle));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveDown(MOVEMENT_OUT_OF_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, MOVE_NOT_POSSIBLE);
}

TEST(PositionManagerTest, MoveDownWrongPosition)
{
    /* Arrange */
    CREATE_MOCK(myMock);
    EXPECT_CALL(myMock, getCurrentPosition()).WillOnce(Return(out_of_range));
    EXPECT_CALL(myMock, setNewPostion(_)).Times(0);

    /* Act */
    MovementStatus status = moveDown(MOVEMENT_IN_RANGE_FOR_MIDDLE);

    /* Assert */
    EXPECT_EQ(status, POSITION_WRONG);
}
