#ifndef __tuts__GLSLProgram__
#define __tuts__GLSLProgram__

#include <fstream>
#include <string>
#include <vector>
#include <GLUT/GLUT.h>
#include "Errors.h"

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();
    
    void initShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    void linkShaders();
    void addAttribute(const std::string& attributeName);
    void use();
    void unuse();
    GLint getUniformLocation(const std::string& uniformName);
    GLint getAttribLocation(const std::string& attribName);
    
private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
    GLuint m_vaoID;
    int m_numAttributes;
    
    void compileShader(const std::string& filePath, GLuint shaderID);
    
};

#endif /* defined(__tuts__GLSLProgram__) */
