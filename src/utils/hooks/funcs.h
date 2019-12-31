#ifndef HOOK_FUNCS_H
#define HOOK_FUNCS_H


#define DECL_HOOK(return_type, name, ...) \
typedef return_type (*name ## _t)( __VA_ARGS__ ); \
extern name ## _t orig_ ## name; \
return_type name ( __VA_ARGS__ );

#define DEF_HOOK(name) \
name ## _t orig_ ## name;


#define ADD_HOOK(name, place) \
orig_ ## name = place -> name; \
place -> name = name;


#define CALL_ORIG(name, ...) \
orig_ ## name ( __VA_ARGS__ )



#endif // HOOK_FUNCS_H