#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0) {

}

GLSLProgram::~GLSLProgram() {
    
}

void GLSLProgram::initShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    _programID = glCreateProgram();
    
    //VERTEX SHADER
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created!");
    }
    compileShader(vertexShaderFilePath, _vertexShaderID);
    
    //FRAGMENT SHADER
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created!");
    }
    compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint shaderID) {
    std::ifstream file(filePath);
    if (file.fail()) {
        fatalError("Failed to open " + filePath);
    }
    
    std::string fileContents = "";
    std::string line;
    
    while (std::getline(file, line)) {
        fileContents += line + "\n";
    }
    
    file.close();
    
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(shaderID, 1, &contentsPtr, nullptr);
    glCompileShader(shaderID);
    
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    
    //error checking
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
        
        glDeleteShader(shaderID);
        
        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + filePath + " failed to compile!");
    }
}

//bleeehhhh
void GLSLProgram::linkShaders() {
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);
    
    glLinkProgram(_programID);
    
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
        
        glDeleteProgram(_programID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
        
        std::printf("%s\n", &infoLog[0]);
        fatalError("Shaders failed to link!");
    }
    
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
    //glGetAttribLocation(_programID, attributeName.c_str());
    //_numAttributes++;
    glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++) {
        //glBindVertexArray(i);
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
    GLint location = glGetUniformLocation(_programID, uniformName.c_str());
    if (location == GL_INVALID_VALUE) {
        fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;
}

GLint GLSLProgram::getAttribLocation(const std::string& attribName) {
    GLint location = glGetAttribLocation(_programID, attribName.c_str());
    if (location == GL_INVALID_VALUE) {
        fatalError("Uniform " + attribName + " not found in shader!");
    }
    return location;
}