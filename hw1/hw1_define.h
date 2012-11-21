#ifndef _HW1_DEFINE_H_
#define _HW1_DEFINE_H_

namespace csci561
{

//#define HW1_DEBUG

enum MovAction_t
{
    MOV_ACT_NOOP = 1,
    MOV_ACT_RIGHT,
    MOV_ACT_DOWN,
    MOV_ACT_LEFT,
    MOV_ACT_TOP,
};

const int NO_OP = -1;
const int OP_OK = 0;

} //namespac

#endif
