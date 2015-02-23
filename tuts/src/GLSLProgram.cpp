#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_numAttributes(0) {

}

GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::initShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    m_programID = glCreateProgram();
    
    //VERTEX SHADER
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created!");
    }
    compileShader(vertexShaderFilePath, m_vertexShaderID);
    
    //FRAGMENT SHADER
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created!");
    }
    compileShader(fragmentShaderFilePath, m_fragmentShaderID);
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
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    
    glLinkProgram(m_programID);
    
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);
        
        glDeleteProgram(m_programID);
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);
        
        std::printf("%s\n", &infoLog[0]);
        fatalError("Shaders failed to link!");
    }
    
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
    //glGetAttribLocation(m_programID, attributeName.c_str());
    //m_numAttributes++;
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
    glUseProgram(m_programID);
    for (int i = 0; i < m_numAttributes; i++) {
        //glBindVertexArray(i);
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < m_numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
    GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
    if (location == GL_INVALID_VALUE) {
        fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;
}

GLint GLSLProgram::getAttribLocation(const std::string& attribName) {
    GLint location = glGetAttribLocation(m_programID, attribName.c_str());
    if (location == GL_INVALID_VALUE) {
        fatalError("Attribute " + attribName + " not found in shader!");
    }
    return location;
}