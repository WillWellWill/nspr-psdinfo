#ifndef __INTERACT_COMMON_H__
#define __INTERACT_COMMON_H__

#define SAFE_DELETE(p) if (p) delete p
#define SAFE_DELETE_ARRAY(P) if(p) delete p[]
#define SAFE_ALLOC(p,type,n) p = new type[n]; if (!p) return false


#define COM_STR_METHOD_LENGTH 10 //request method
#define COM_STR_LENGTH 100
#define COM_LENGTH 1024
#define COM_CONTENT_LENGTH 4096
#endif
