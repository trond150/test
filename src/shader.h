#pragma once
#include <string>

class Shader
{
public:
    Shader(const std::string& vertex_path, const std::string& fragment_path);

    void use();

    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;

private:
    std::string read_file(const std::string& path) const;

    unsigned int id;

};