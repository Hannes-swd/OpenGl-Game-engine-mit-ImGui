#ifndef GLAD_GL_H_
#define GLAD_GL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*GLADloadproc)(const char *name);

int gladLoadGLLoader(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif /* GLAD_GL_H_ */