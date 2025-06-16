#ifndef VOICE_MODULE_H
#define VOICE_MODULE_H



#define FORWARD   (0)
#define BACKWARD  (1)
#define STOP      (2)
#define LEFT      (3)
#define RIGHT     (4)

ES_t voice_module_init(void);
int  voice_module_recognize(void);

#endif