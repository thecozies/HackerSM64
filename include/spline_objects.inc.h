#pragma once

// bparam1
enum SplineObjectBehaviors {
    // continue moving in bparam2 direction
    SPLINE_OBJECT_BHV_AUTO,
    // mario standing on it moves from spline start to end, bparam2 dir is start position (beginning or end of spline)
    SPLINE_OBJECT_BHV_MARIO_ACTIVATES,
};

// bparam2
enum SplineObjectDirections {
    SPLINE_OBJECT_MOVE_FORWARD,
    SPLINE_OBJECT_MOVE_BACKWARDS,
    SPLINE_OBJECT_MOVE_BACK_AND_FORTH,
    SPLINE_OBJECT_MOVE_BACK_AND_FORTH_REVERSED, // same as back and forth but starts in the opposite direction
};

// bparam3, speed in units per frame