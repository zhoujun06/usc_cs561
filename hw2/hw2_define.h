#ifndef _HW2_DEFINE_H_
#define _HW2_DEFINE_H_

namespace csci561
{

//#define HW2_DEBUG


enum MovAction_t
{
    MOV_ACT_NOOP = 1,
    MOV_ACT_LEFT,
    MOV_ACT_TOP,
    MOV_ACT_RIGHT,
    MOV_ACT_DOWN,
};

const int NO_OP = -1;
const int OP_OK = 0;

} //namespac

#endif
