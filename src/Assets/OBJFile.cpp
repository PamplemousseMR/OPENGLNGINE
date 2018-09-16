#include "Assets/OBJFile.hpp"
#include "Assets/Object.hpp"
#include "Assets/Group.hpp"
#include "Assets/Material.hpp"
#include "Assets/Map.hpp"
#include "Component/Mesh.hpp"

#include <glm/vec2.hpp>

#include <chrono>
#include <fstream>

using namespace std;
using namespace glm;
using namespace std::chrono;
using namespace Component;

namespace Assets
{

vector<string> OBJFile::split(const string& _str, char _splitter) noexcept
{
    if (_str == "")
    {
        return vector<string>(0);
    }
    vector<size_t> semicolons;
    vector<string> tokens;
    for(size_t i = 0; i < _str.length(); ++i)
    {
        if (_str[i] == _splitter)
        {
            semicolons.push_back(i);
        }
    }

    if (semicolons.size() == 0)
    {
        tokens.push_back(_str);
        return tokens;
    }

    for(size_t i = 0; i<semicolons.size() + 1; ++i)
    {
        if (i == 0)
        {
            tokens.push_back(_str.substr(0, semicolons[i]));
        }
        else if (i == semicolons.size())
        {
            tokens.push_back(_str.substr(semicolons[i - 1] + 1));
        }
        else
        {
            tokens.push_back(_str.substr(semicolons[i - 1] + 1, semicolons[i] - semicolons[i - 1] - 1));
        }
    }
    return tokens;
}

vector<string> OBJFile::removeNullptr(const vector<string>& _str) noexcept
{
    vector<string> res;
    for(unsigned int i(0); i < _str.size(); ++i)
    {
        if (_str[i] != "")
        {
            res.push_back(_str[i]);
        }
    }
    return res;
}

void OBJFile::push(vector<vec3>* _vertex, vector<vec3>* _normal, vector<vec2>* _textCoord, vector<vec3>* _index, string* _usemtl) const
{
    if (_usemtl == nullptr)
    {
        throw(invalid_argument("[OBJFile] usemtl can`t be nullptr"));
    }

    vec3 vec = _index->back();
    if(long(vec[1]) != 0 && _textCoord->size() == 0)
    {
        throw(invalid_argument("[OBJFile] use texture coord on faces with no texture coord define"));
    }
    if (long(vec[2]) != 0 && _normal->size() == 0)
    {
        throw(invalid_argument("[OBJFile] use normal on faces with no normal define"));
    }
    try
    {
        if (*_usemtl != "")
        {
            m_objects.back()->getLastGroup()->add(*_vertex, _normal->size() > 0 ? _normal : nullptr, _textCoord->size() > 0 ? _textCoord : nullptr, *_index, _usemtl);
        }
        else
        {
            m_objects.back()->getLastGroup()->add(*_vertex, _normal->size() > 0 ? _normal : nullptr, _textCoord->size() > 0 ? _textCoord : nullptr, *_index, nullptr);
        }
    }
    catch(const invalid_argument& _e)
    {
        throw(invalid_argument("[OBJFile] " + string(string(_e.what()))));
    }
    _index->clear();
    *_usemtl = "";
}

vector<Material*> OBJFile::findMaterial(const string& _mtl) const noexcept
{
    vector<Material*> m;
    for(Object* ob : m_objects)
    {
        for(Group* gp : ob->getGroups())
        {
            for(Mesh* ms : gp->getMeshs())
            {
                Material* ma = ms->getMaterial();
                if (ma && ma->getName() == _mtl)
                {
                    m.push_back(ma);
                }
            }
        }
    }
    return m;
}

void OBJFile::checkSize(const vector<string>& _vec, size_t _min, size_t _max, int _linuNumber)
{
    const string symbol = "[OBJFile] unexpected symbol at the end of the line ";
    const string invalidData = "[OBJFile] missing value(s) at the line ";
    if (_vec.size() < _min)
    {
        throw invalid_argument(invalidData + to_string(_linuNumber));
    }
    if (_vec.size() > _max)
    {
        throw invalid_argument(symbol + to_string(_linuNumber));
    }
}

void OBJFile::loadMTLFile(const std::filesystem::path& _path) const
{
    if(!filesystem::exists(_path) || !filesystem::is_regular_file(_path))
    {
        throw invalid_argument("[OBJFile] path doesn't exists : " + _path.string());
    }

    if(_path.extension() != ".mtl")
    {
        throw invalid_argument("[OBJFile] can't read '" + _path.extension().string() + "' extension");
    }

    const string invalidData = "[OBJFile] missing value(s) at the line ";
    const string cmd = "[OBJFile] invalide commande at the line ";
    const string noexiste = "[OBJFile] set value to non existe material at line ";
    const string commande = "[OBJFile] unknow commande at line ";
    const string lineError = "[OBJFile] Unexpected symbol at the line ";
    int lineNumber = 0;

    ifstream file(_path, ios::in);
    if (!file)
    {
        throw invalid_argument("[OBJFile] can't open mtl file : " + _path.string());
    }
    vector<Material*> materials;
    string line;

    while (getline(file, line, '\n'))
    {
        lineNumber++;
        vector<string> data = removeNullptr(split(line, ' '));
        if (data.size() > 0)
        {
            string dat0 = data[0];
            if (dat0 == "newmtl")
            {
                checkSize(data, 2, 2, lineNumber);
                materials = findMaterial(data[1]);
                if (materials.size() == 0)
                {
                    throw invalid_argument("[OBJFile] Material " + data[1] + " not used at the line " + to_string(lineNumber));
                }
            }
            else if(dat0 != "#")
            {
                if (materials.size() == 0)
                {
                    throw invalid_argument(noexiste + to_string(lineNumber));
                }
                if (dat0 == "\tKa" || dat0 == "Ka" || dat0 == "\tka" || dat0 == "ka")
                {
                    checkSize(data, 4, 4, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setAmbient(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tKd" || dat0 == "Kd" || dat0 == "\tkd" || dat0 == "kd")
                {
                    checkSize(data, 4, 4, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setDiffuse(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tKs" || dat0 == "Ks" || dat0 == "\tks" || dat0 == "ks")
                {
                    checkSize(data, 4, 4, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setSpecular(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tKe" || dat0 == "Ke" || dat0 == "\tke" || dat0 == "ke")
                {
                    checkSize(data, 4, 4, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setEmissiveCoeficient(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tTf" || dat0 == "Tf" || dat0 == "\ttf" || dat0 == "tf")
                {
                    checkSize(data, 4, 4, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setTransmissionFilter(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tillum" || dat0 == "illum")
                {
                    checkSize(data, 2, 2, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setIllumination(stoi(data[1]));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\td" || dat0 == "d")
                {
                    checkSize(data, 2, 3, lineNumber);
                    if (data.size() == 2)
                    {
                        for(Material* ma : materials)
                        {
                            try
                            {
                                ma->setDissolve(stof(data[1]));
                            }
                            catch(const exception&)
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else
                    {
                        for(Material* ma : materials)
                        {
                            ma->setDissolve(stof(data[2]));
                        }
                        string com = data[1];
                        if (com != "-halo")
                        {
                            throw invalid_argument(commande + to_string(lineNumber));
                        }
                        for(Material* ma : materials)
                        {
                            ma->setHalo(true);
                        }
                    }
                }
                else if (dat0 == "\tNs" || dat0 == "Ns" || dat0 == "\tns" || dat0 == "ns")
                {
                    checkSize(data, 2, 2, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setSpecularExponent(stof(data[1]));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tsharpness" || dat0 == "sharpness")
                {
                    checkSize(data, 2, 2, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setSharpness(stof(data[1]));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else if (dat0 == "\tNi" || dat0 == "Ni" || dat0 == "\tni" || dat0 == "ni")
                {
                    checkSize(data, 2, 2, lineNumber);
                    for(Material* ma : materials)
                    {
                        try
                        {
                            ma->setopticalDensity(stof(data[1]));
                        }
                        catch(const exception&)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                    }
                }
                else
                {
                    if (data.size() < 2)
                    {
                        throw invalid_argument(invalidData + to_string(lineNumber));
                    }
                    vector<Map*> map;
                    if (dat0 == "\tmap_Ka" || dat0 == "map_Ka" || dat0 == "\tmap_ka" || dat0 == "map_ka")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setKamap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getKamap());
                        }
                    }
                    else if (dat0 == "\tmap_Kd" || dat0 == "map_Kd" || dat0 == "\tmap_kd" || dat0 == "map_kd")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setKdmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getKdmap());
                        }
                    }
                    else if (dat0 == "\tmap_Ks" || dat0 == "map_Ks" || dat0 == "\tmap_ks" || dat0 == "map_ks")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setKsmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getKsmap());
                        }
                    }
                    else if (dat0 == "\tmap_Ns" || dat0 == "map_Ns" || dat0 == "\tmap_ns" || dat0 == "map_ns")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setNsmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getKsmap());
                        }
                    }
                    else if (dat0 == "\tmap_d" || dat0 == "map_d")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setdmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getdmap());
                        }
                    }
                    else if (dat0 == "\tdisp" || dat0 == "disp" || dat0 == "\tmap_Disp" || dat0 == "map_Disp")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setDispmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getDispmap());
                        }
                    }
                    else if (dat0 == "\tdecal" || dat0 == "decal")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setDecalmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getDecalmap());
                        }
                    }
                    else if (dat0 == "\tbump" || dat0 == "bump" || dat0 == "\tmap_bump" || dat0 == "map_bump")
                    {
                        try
                        {
                            for(Material* ma : materials)
                            {
                                ma->setBumpmap(_path.parent_path() / data[data.size() - 1]);
                            }
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] [loadMTLFile] " + string(_e.what()));
                        }
                        for(Material* ma : materials)
                        {
                            map.push_back(ma->getBumpmap());
                        }
                    }
                    else
                    {
                        throw invalid_argument(lineError + to_string(lineNumber) + " : \"" + dat0 + "\"");
                    }
                    if (map.size() != 0)
                    {
                        for(size_t i = 1 ; i < data.size() - 1 ; ++i)
                        {
                            if (data[i] == "-bm")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setMult(stof(data[i+1]));
                                }
                                ++i;
                            }
                            else if (data[i] == "-clamp")
                            {
                                if (data[i + 1] != "on" && data[i + 1] != "off")
                                {
                                    throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");
                                }
                                for(Map* umap : map)
                                {
                                    umap->setClamp(data[i + 1] == "on" ? true : false);
                                }
                                ++i;
                            }
                            else if (data[i] == "-blendu")
                            {
                                if (data[i + 1] != "on" && data[i + 1] != "off")
                                {
                                    throw invalid_argument(lineError + to_string(lineNumber) + " for blendu value");
                                }
                                for(Map* umap : map)
                                    umap->setBlendu(data[i + 1] == "on" ? true : false);
                                ++i;
                            }
                            else if (data[i] == "-blendv")
                            {
                                if (data[i + 1] != "on" && data[i + 1] != "off")
                                {
                                    throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");
                                }
                                for(Map* umap : map)
                                {
                                    umap->setBlendv(data[i + 1] == "on" ? true : false);
                                }
                                ++i;
                            }
                            else if (data[i] == "-blendv")
                            {
                                if (data[i + 1] != "on" && data[i + 1] != "off")
                                {
                                    throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");
                                }
                                for(Map* umap : map)
                                {
                                    umap->setBlendv(data[i + 1] == "on" ? true : false);
                                }
                                ++i;
                            }
                            else if (data[i] == "-mm")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setBase(stof(data[i + 1]));
                                    umap->setGain(stof(data[i + 2]));
                                }

                            }
                            else if (data[i] == "-o")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setO(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                }
                                i += 3;
                            }
                            else if (data[i] == "-s")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setS(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                }
                                i += 3;
                            }
                            else if (data[i] == "-t")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setT(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                }
                                i += 3;
                            }
                            else if (data[i] == "-textres")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setTextres(stoi(data[i + 1]));
                                }
                                ++i;
                            }
                            else if (data[i] == "-cc")
                            {
                                if (data[i + 1] != "on" && data[i + 1] != "off")
                                {
                                    throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");
                                }
                                for(Map* umap : map)
                                {
                                    umap->setCc(data[i + 1] == "on" ? true : false);
                                }
                                ++i;
                            }
                            else if (data[i] == "-boost")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setBoost(stof(data[i + 1]));
                                }
                                ++i;
                            }
                            else if (data[i] == "-imfchan")
                            {
                                for(Map* umap : map)
                                {
                                    umap->setImfchanrgb(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                    umap->setImfchanmlz(vec3(stof(data[i + 4]), stof(data[i + 5]), stof(data[i + 6])));
                                }
                                i += 6;
                            }
                            else
                            {
                                throw invalid_argument(cmd + to_string(lineNumber) + " : " + dat0);
                            }
                        }
                    }
                }
            }
        }
    }
    file.close();
}

OBJFile::OBJFile() noexcept
{
}

OBJFile::~OBJFile() noexcept
{
    for(Object* m : m_objects)
    {
        delete m;
    }
}

OBJFile::OBJFile(const OBJFile& _objfile) :
    m_name(_objfile.m_name)
{
    for(Object* o : _objfile.m_objects)
    {
        m_objects.push_back(new Object(*o));
    }
}

OBJFile::OBJFile(OBJFile&& _objfile) :
    m_name(std::move(_objfile.m_name))
{
    for (size_t i=0 ; i<_objfile.m_objects.size() ; ++i)
    {
        m_objects.push_back(_objfile.m_objects[i]);
        _objfile.m_objects[i] = nullptr;
    }
}

OBJFile& OBJFile::operator=(const OBJFile& _objfile)
{
    if(this != &_objfile)
    {
        for(Object* m : m_objects)
        {
            delete m;
        }
        m_objects.clear();
        for(Object* o : _objfile.m_objects)
        {
            m_objects.push_back(new Object(*o));
        }
        m_name = _objfile.m_name;
    }
    return *this;
}

OBJFile& OBJFile::operator=(OBJFile&& _objfile)
{
    if(this != &_objfile)
    {
        for(Object* m : m_objects)
        {
            delete m;
        }
        m_objects.clear();
        m_name = std::move(_objfile.m_name);
        for (size_t i=0 ; i<_objfile.m_objects.size() ; ++i)
        {
            m_objects.push_back(_objfile.m_objects[i]);
            _objfile.m_objects[i] = nullptr;
        }
    }
    return *this;
}

void OBJFile::load(const filesystem::path& _path)
{
    for(Object* m : m_objects)
    {
        delete m;
    }

    if(!filesystem::exists(_path) || !filesystem::is_regular_file(_path))
    {
        throw invalid_argument("[OBJFile] path doesn't exists : " + _path.string());
    }

    if(_path.extension() != ".obj")
    {
        throw invalid_argument("[OBJFile] can't read '" + _path.extension().string() + "' extension");
    }

    m_name = _path.filename().string();
    ifstream file(_path, ios::in);
    if (!file)
    {
        throw invalid_argument("[OBJFile] Can't open file : " + _path.string());
    }

    const string symbol = "[OBJFile] Unexpected symbol at the end of the line ";
    const string invalidData = "[OBJFile] Missing value(s) at the line ";
    const string lineError = "[OBJFile] Unexpected symbol at the line ";

    vector<vec3> vertex(0);
    vector<vec3> normal(0);
    vector<vec2> textCoord(0);
    vector<vec3> index;
    string line;
    string mtllib = "";
    string usemtl = "";
    int lineNumber = 0;

    while (getline(file, line, '\n'))
    {
        ++lineNumber;
        vector<string> data = removeNullptr(split(line, ' '));
        if (data.size() > 0)
        {
            string dat0 = data[0];
            if (dat0 != "v" && dat0 != "vn" && dat0 != "vt" && dat0 != "f" && dat0 != "o" && dat0 != "g" && dat0 != "#" && dat0 != "usemtl" && dat0 != "mtllib" && dat0 != "s")
            {
                throw invalid_argument(lineError + to_string(lineNumber));
            }
            if (dat0 == "v" || dat0 == "vn")
            {
                checkSize(data, 4, 4, lineNumber);
                vec3 val;
                for(size_t i = 1 ; i<=3 ; ++i)
                {
                    try
                    {
                        val[glm::vec3::length_type(i - 1)] = stof(data[i]);
                    }
                    catch(const invalid_argument&)
                    {
                        throw invalid_argument(invalidData + to_string(lineNumber));
                    }
                }
                if (dat0 == "vn")
                {
                    normal.push_back(val);
                }
                else if (dat0 == "v")
                {
                    vertex.push_back(val);
                }
            }
            else if (dat0 == "vt")
            {
                checkSize(data, 3, 4, lineNumber);
                vec2 val;
                for(size_t i = 1; i <= 2; ++i)
                {
                    try
                    {
                        val[glm::vec3::length_type(i - 1)] = stof(data[i]);
                    }
                    catch(const invalid_argument&)
                    {
                        throw invalid_argument(invalidData + to_string(lineNumber));
                    }
                }
                textCoord.push_back(val);
            }
            else if (dat0 == "f")
            {
                checkSize(data, 4, 5, lineNumber);
                vec3 val;
                short end = data.size() == 4 ? 1 : 3;
                for(short k=0 ; k<end ; k+=2)
                {
                    for(short i=0+k ; i<=2+k ; ++i)
                    {
                        vector<string> d = split(data[i%4+1], '/');
                        if (d.size() > 3)
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                        if (d.size() == 1)
                        {
                            try
                            {
                                val[0] = stof(d[0]);
                            }
                            catch(const invalid_argument&)
                            {
                                throw invalid_argument(invalidData + to_string(lineNumber));
                            }
                            val[1] = 0;
                            val[2] = 0;
                        }
                        else if (d.size() == 2)
                        {
                            try
                            {
                                float temp = stof(d[0]);
                                val[0] = temp;
                                temp = stof(d[1]);
                                val[1] = temp;
                                val[2] = 0;
                            }
                            catch(const invalid_argument&)
                            {
                                throw invalid_argument(invalidData + to_string(lineNumber));
                            }
                        }
                        else if (d.size() == 3)
                        {
                            float temp;
                            try
                            {
                                temp = stof(d[0]);
                            }
                            catch(const invalid_argument&)
                            {
                                throw invalid_argument(invalidData + to_string(lineNumber));
                            }
                            val[0] = temp;

                            if (d[1] == "")
                            {
                                val[1] = 0;
                            }
                            else
                            {
                                try
                                {
                                    temp = stof(d[1]);
                                    val[1] = temp;
                                }
                                catch(const invalid_argument&)
                                {
                                    throw invalid_argument(invalidData + to_string(lineNumber));
                                }
                            }

                            try
                            {
                                temp = stof(d[2]);
                            }
                            catch(const invalid_argument&)
                            {
                                throw invalid_argument(invalidData + to_string(lineNumber));
                            }
                            val[2] = temp;
                        }
                        else
                        {
                            throw invalid_argument(lineError + to_string(lineNumber));
                        }
                        index.push_back(val);
                    }
                }
            }
            else if (dat0 == "o")
            {
                checkSize(data, 2, 2, lineNumber);
                if (index.size() != 0)
                {
                    if (m_objects.size() > 0)
                    {
                        if (m_objects.back()->getGroups().size() > 0)
                        {
                            try
                            {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch(const invalid_argument& _e)
                            {
                                throw invalid_argument("[OBJFile] " + string(_e.what()));
                            }
                        }
                        else
                        {
                            m_objects.back()->addGroup("default_group");
                            try
                            {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch(const invalid_argument& _e)
                            {
                                throw invalid_argument("[OBJFile] " + string(_e.what()));
                            }
                        }
                    }
                    if (index.size() != 0)
                    {
                        m_objects.push_back(new Object("default_object"));
                        m_objects.back()->addGroup("default_group");
                        try
                        {
                            push(&vertex, &normal, &textCoord, &index, &usemtl);
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] " + string(_e.what()));
                        }
                    }
                }
                m_objects.push_back(new Object(data[1]));
            }
            else if (dat0 == "g")
            {
                if (data.size() > 2)
                {
                    throw invalid_argument(symbol + to_string(lineNumber));
                }
                if (data.size() == 2)
                {
                    if (m_objects.size() > 0)
                    {
                        if (m_objects.back()->getGroups().size() > 0)
                        {
                            if (index.size() != 0)
                            {
                                try
                                {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                                }
                                catch(const invalid_argument& _e)
                                {
                                    throw invalid_argument("[OBJFile] " + string(_e.what()));
                                }
                            }
                            m_objects.back()->addGroup(data[1]);
                        }
                        else
                        {
                            if (index.size() != 0)
                            {
                                m_objects.back()->addGroup("default_group");
                                try
                                {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                                }
                                catch(const invalid_argument& _e)
                                {
                                    throw invalid_argument("[OBJFile] " + string(_e.what()));
                                }
                            }
                            m_objects.back()->addGroup(data[1]);
                        }
                    }
                    else
                    {
                        if (index.size() != 0)
                        {
                            m_objects.push_back(new Object("default_object"));
                            m_objects.back()->addGroup("default_group");
                            try
                            {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch(const invalid_argument& _e)
                            {
                                throw invalid_argument("[OBJFile] " + string(_e.what()));
                            }
                        }
                        m_objects.push_back(new Object("default_object"));
                        m_objects.back()->addGroup(data[1]);
                    }
                }
            }
            else if (dat0 == "mtllib")
            {
                checkSize(data, 2, 2, lineNumber);
                mtllib = data[1];
            }
            else if (dat0 == "usemtl")
            {
                checkSize(data, 2, 2, lineNumber);
                if (index.size() > 0)
                {
                    if (m_objects.size() > 0)
                    {
                        if (m_objects.back()->getGroups().size() > 0)
                        {
                            try
                            {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch(const invalid_argument& _e)
                            {
                                throw invalid_argument("[OBJFile] " + string(_e.what()));
                            }
                        }
                        else
                        {
                            m_objects.back()->addGroup("default_group");
                            try
                            {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch(const invalid_argument& _e)
                            {
                                throw invalid_argument("[OBJFile] " + string(_e.what()));
                            }
                        }
                    }
                    else
                    {
                        m_objects.push_back(new Object("default_object"));
                        m_objects.back()->addGroup("default_group");
                        try
                        {
                            push(&vertex, &normal, &textCoord, &index, &usemtl);
                        }
                        catch(const invalid_argument& _e)
                        {
                            throw invalid_argument("[OBJFile] " + string(_e.what()));
                        }
                    }
                }
                usemtl = data[1];
            }
        }
    }

    if (index.size() > 0)
    {
        if (m_objects.size() > 0)
        {
            if (m_objects.back()->getGroups().size() > 0)
            {
                try
                {
                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                }
                catch(const invalid_argument& _e)
                {
                    throw invalid_argument("[OBJFile] " + string(_e.what()));
                }
            }
            else
            {
                m_objects.back()->addGroup("default_group");
                try
                {
                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                }
                catch(const invalid_argument& _e)
                {
                    throw invalid_argument("[OBJFile] " + string(_e.what()));
                }
            }
        }
        else
        {
            m_objects.push_back(new Object("default_group"));
            m_objects.back()->addGroup("default_group");
            try
            {
                push(&vertex, &normal, &textCoord, &index, &usemtl);
            }
            catch(const invalid_argument& _e)
            {
                throw invalid_argument("[OBJFile] " + string(_e.what()));
            }
        }
    }


    file.close();
    if (mtllib != "")
    {
        try
        {
            loadMTLFile(_path.parent_path() / mtllib);
        }
        catch(invalid_argument e)
        {
            throw invalid_argument("[OBJFile] [load(const string& path) throw()] " + string(e.what()));
        }
    }
}

ostream& OBJFile::print(ostream& _o) const noexcept
{
    _o << "[OBJFile " << m_name << "]";
    for(const Object* ob : m_objects)
    {
        _o << "\t" << *ob;
    }
    return _o;
}

const vector<Object*>& OBJFile::getObjects() const noexcept
{
    return m_objects;
}

ostream& operator<<(ostream& o, const OBJFile& m) noexcept
{
    m.print(o);
    return o;
}

}
