#include "Asset/OBJFile.hpp"
#include "Asset/Object.hpp"
#include "Asset/Group.hpp"
#include "Asset/Material.hpp"
#include "Asset/Map.hpp"

using namespace std;
using namespace glm;
using namespace std::chrono;
using namespace Component;

namespace Assets
{

    vector<string> OBJFile::split(const string & str, char splitter) const
    {
        if (str == "") return vector<string>(0);
        vector<int> semicolons;
        vector<string> tokens;
        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] == splitter)
                semicolons.push_back((int)i);
        }

        if (semicolons.size() == 0)
        {
            tokens.push_back(str);
            return tokens;
        }

        for (size_t i = 0; i<semicolons.size() + 1; i++) {
            if (i == 0)
                tokens.push_back(str.substr(0, semicolons[i]));
            else if (i == semicolons.size())
                tokens.push_back(str.substr(semicolons[i - 1] + 1));
            else
                tokens.push_back(str.substr(semicolons[i - 1] + 1, semicolons[i] - semicolons[i - 1] - 1));
        }
        return tokens;
    }

    vector<string> OBJFile::removenullptr(const vector<string> & str) const
    {
        vector<string> res;
        for (unsigned int i(0); i < str.size(); i++)
            if (str[i] != "")
                res.push_back(str[i]);
        return res;
    }

    void OBJFile::push(vector<vec3>* vertex, vector<vec3>* normal, vector<vec2>* textCoord, vector<vec3>* index, string* usemtl) const throw()
    {
        if (usemtl == nullptr)throw(invalid_argument("[OBJFile " + m_name + "] [push(vector<vec3>* vertex, vector<vec3>* normal, vector<vec2>* textCoord, vector<vec3>* index, string* usemtl) const throw()] usemtl can`t be nullptr"));
        if(index->size() < 0)
            throw(invalid_argument("[OBJFile " + m_name + "] [push(vector<vec3>* vertex, vector<vec3>* normal, vector<vec2>* textCoord, vector<vec3>* index, string* usemtl) const throw()] push with no index"));
        else
        {
            vec3 vec = index->back();
            if(vec[1] != 0 && textCoord->size() == 0)
                throw(invalid_argument("[OBJFile " + m_name + "] [push(vector<vec3>* vertex, vector<vec3>* normal, vector<vec2>* textCoord, vector<vec3>* index, string* usemtl) const throw()] use texture coord on faces with no texture coord define"));
            if (vec[2] != 0 && normal->size() == 0)
                throw(invalid_argument("[OBJFile " + m_name + "] [push(vector<vec3>* vertex, vector<vec3>* normal, vector<vec2>* textCoord, vector<vec3>* index, string* usemtl) const throw()] use normal on faces with no normal define"));
        }
        try {
            if (*usemtl != "")
                m_objects.back()->getLastGroup()->add(*vertex, normal->size() > 0 ? normal : nullptr, textCoord->size() > 0 ? textCoord : nullptr, *index, usemtl);
            else
                m_objects.back()->getLastGroup()->add(*vertex, normal->size() > 0 ? normal : nullptr, textCoord->size() > 0 ? textCoord : nullptr, *index, nullptr);
        }
        catch(invalid_argument e){
            throw(invalid_argument("[OBJFile " + m_name + "] [push(vector<vec3>* vertex, vector<vec3>* normal, vector<vec2>* textCoord, vector<vec3>* index, string* usemtl) const throw()] " + e.what()));
        }
        index->clear();
        *usemtl = "";
    }

    vector<Material*> OBJFile::findMaterial(const string& mtl) const
    {
        vector<Material*> m;
        for (Object* ob : m_objects)
            for (Group* gp : ob->getGroups())
                for (Material* ma : gp->getMaterials())
                    if (ma && ma->getName() == mtl)
                        m.push_back(ma);
        return m;
    }

    void OBJFile::loadMTLFile(const string& path) const throw()
    {
#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] [loadMTLFile(const string& path) throw()] load..."<<endl;
#endif
        vector<string> filename = split(path, '.');
        if (filename[filename.size() - 1] != "mtl")
            throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] can't read " + filename[filename.size() - 1] + " extension");
        string symbol = "[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] unexpected symbol at the end of the line ";
        string invalideData = "[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] missing value(s) at the line ";
        string cmd = "[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] invalide commande at the line ";
        string noexiste = "[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] set value to non existe material at line ";
        string commande = "[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] unknow commande at line ";
        string lineError = "[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] Unexpected symbol at the line ";
        int lineNumber = 0;
        ifstream file(path, ios::in);
        if (!file)
            throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile(const string& path) throw()] can't open mtl file " + path);
        vector<Material*> materials;
        string line;
        filename = split(filename[0], '/');
        string res = "";
        for (int i(0); i < filename.size() - 1; i++)
            res += filename[i] + "/";
        while (getline(file, line, '\n'))
        {
            lineNumber++;
            vector<string> data = removenullptr(split(line, ' '));
            if (data.size() > 0)
            {
                string dat0 = data[0];
                if (dat0 == "newmtl")
                {
                    if (data.size() < 2)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 2)
                        throw invalid_argument(symbol + to_string(lineNumber));
                        materials = findMaterial(data[1]);
                        if (materials.size() == 0)
                        {
                            cerr << "\t[OBJFile " << m_name << "][loadMTLFile(const string& path) throw()] material " << data[1] << " not used" << endl;
                            bool b = true;
                            while (b && getline(file, line, '\n'))
                            {
                                lineNumber++;
                                vector<string> data = removenullptr(split(line, ' '));
                                if (data.size()>0 && data[0] == "newmtl")
                                {
                                    materials = findMaterial(data[1]);
                                    if (materials.size() != 0)
                                        b = false;
                                    else
                                        cerr << "\t[OBJFile " << m_name << "][loadMTLFile(const string& path) throw()] material " << data[1] << " not used" << endl;
                                }
                            }
                        }
                }
                else if(dat0 != "#"){
                    if (materials.size() == 0)
                        throw invalid_argument(noexiste + to_string(lineNumber));
                    if (dat0 == "\tKa" || dat0 == "Ka" || dat0 == "\tka" || dat0 == "ka")
                    {
                        if (data.size() < 4)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 4)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try {
                                ma->setAmbient(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tKd" || dat0 == "Kd" || dat0 == "\tkd" || dat0 == "kd")
                    {
                        if (data.size() < 4)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 4)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials) {
                            try{
                                ma->setDiffuse(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tKs" || dat0 == "Ks" || dat0 == "\tks" || dat0 == "ks")
                    {
                        if (data.size() < 4)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 4)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try{
                                ma->setSpecular(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tKe" || dat0 == "Ke" || dat0 == "\tke" || dat0 == "ke")
                    {
                        if (data.size() < 4)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 4)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials) {
                            try {
                                ma->setEmissiveCoeficient(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tTf" || dat0 == "Tf" || dat0 == "\ttf" || dat0 == "tf")
                    {
                        if (data.size() < 4)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 4)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try{
                                ma->setTransmissionFilter(vec3(stof(data[1]), stof(data[2]), stof(data[3])));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tillum" || dat0 == "illum")
                    {
                        if (data.size() < 2)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 2)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try{
                                ma->setIllumination(stoi(data[1]));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\td" || dat0 == "d")
                    {
                        if (data.size() < 2)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 3)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        if (data.size() == 2)
                        {
                            for (Material* ma : materials)
                            {
                                try{
                                    ma->setDissolve(stof(data[1]));
                                }
                                catch (exception e) 
                                {
                                    throw invalid_argument(lineError + to_string(lineNumber));
                                }
                            }
                        }
                        else
                        {
                            for (Material* ma : materials)
                                ma->setDissolve(stof(data[2]));
                            string com = data[1];
                            if (com != "-halo")
                                throw invalid_argument(commande + to_string(lineNumber));
                            for (Material* ma : materials)
                                ma->setHalo(true);
                        }
                    }
                    else if (dat0 == "\tNs" || dat0 == "Ns" || dat0 == "\tns" || dat0 == "ns")
                    {
                        if (data.size() < 2)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 2)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try {
                                ma->setSpecularExponent(stof(data[1]));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tsharpness" || dat0 == "sharpness")
                    {
                        if (data.size() < 2)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 2)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try{
                                ma->setSharpness(stof(data[1]));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else if (dat0 == "\tNi" || dat0 == "Ni" || dat0 == "\tni" || dat0 == "ni")
                    {
                        if (data.size() < 2)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        if (data.size() > 2)
                            throw invalid_argument(symbol + to_string(lineNumber));
                        if (materials.size() == 0)
                            throw invalid_argument(noexiste + to_string(lineNumber));
                        for (Material* ma : materials)
                        {
                            try{
                                ma->setopticalDensity(stof(data[1]));
                            }
                            catch (exception e) 
                            {
                                throw invalid_argument(lineError + to_string(lineNumber));
                            }
                        }
                    }
                    else {
                        if (data.size() < 2)
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        vector<Map*> map;
                        if (dat0 == "\tmap_Ka" || dat0 == "map_Ka" || dat0 == "\tmap_ka" || dat0 == "map_ka")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setKamap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getKamap());
                        }
                        else if (dat0 == "\tmap_Kd" || dat0 == "map_Kd" || dat0 == "\tmap_kd" || dat0 == "map_kd")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setKdmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getKdmap());
                        }
                        else if (dat0 == "\tmap_Ks" || dat0 == "map_Ks" || dat0 == "\tmap_ks" || dat0 == "map_ks")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setKsmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getKsmap());
                        }
                        else if (dat0 == "\tmap_Ns" || dat0 == "map_Ns" || dat0 == "\tmap_ns" || dat0 == "map_ns")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setNsmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getKsmap());
                        }
                        else if (dat0 == "\tmap_d" || dat0 == "map_d")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setdmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getdmap());
                        }
                        else if (dat0 == "\tdisp" || dat0 == "disp" || dat0 == "\tmap_Disp" || dat0 == "map_Disp")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setDispmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getDispmap());
                        }
                        else if (dat0 == "\tdecal" || dat0 == "decal")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setDecalmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getDecalmap());
                        }
                        else if (dat0 == "\tbump" || dat0 == "bump" || dat0 == "\tmap_bump" || dat0 == "map_bump")
                        {
                            try {
                                for (Material* ma : materials)
                                    ma->setBumpmap(res + data[data.size() - 1]);
                            }
                            catch (invalid_argument e)
                            {
                                throw invalid_argument("[OBJFile " + m_name + "] [loadMTLFile] " + e.what());
                            }
                            for (Material* ma : materials)
                                map.push_back(ma->getBumpmap());
                        }
                        else 
                        {
                            throw invalid_argument(lineError + to_string(lineNumber) + " : \"" + dat0 + "\"");
                        }
                        if (map.size() != 0)
                        {
                            for (int i(1); i < data.size() - 1; i++)
                            {
                                if (data[i] == "-bm")
                                {
                                    for(Map* umap : map)
                                        umap->setMult(stof(data[i+1]));
                                    i++;
                                }
                                else if (data[i] == "-clamp")
                                {
                                    if (data[i + 1] != "on" && data[i + 1] != "off")
                                        throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");

                                    for (Map* umap : map)
                                    {
                                        
                                        umap->setClamp(data[i + 1] == "on" ? true : false);
                                    }
                                    i++;
                                }
                                else if (data[i] == "-blendu")
                                {
                                    if (data[i + 1] != "on" && data[i + 1] != "off")
                                        throw invalid_argument(lineError + to_string(lineNumber) + " for blendu value");
                                    for (Map* umap : map)
                                        umap->setBlendu(data[i + 1] == "on" ? true : false);
                                    i++;
                                }
                                else if (data[i] == "-blendv")
                                {
                                    if (data[i + 1] != "on" && data[i + 1] != "off")
                                        throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");
                                    for (Map* umap : map)
                                        umap->setBlendv(data[i + 1] == "on" ? true : false);
                                    i++;
                                }
                                else if (data[i] == "-blendv")
                                {
                                    if (data[i + 1] != "on" && data[i + 1] != "off")
                                        throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");
                                    for (Map* umap : map)
                                        umap->setBlendv(data[i + 1] == "on" ? true : false);
                                    i++;
                                }
                                else if (data[i] == "-mm")
                                {
                                    for (Map* umap : map)
                                    {
                                        umap->setBase(stof(data[i + 1]));
                                        umap->setGain(stof(data[i + 2]));
                                    }

                                }
                                else if (data[i] == "-o")
                                {
                                    for (Map* umap : map)
                                        umap->setO(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                    i += 3;
                                }
                                else if (data[i] == "-s")
                                {
                                    for (Map* umap : map)
                                        umap->setS(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                    i += 3;
                                }
                                else if (data[i] == "-t")
                                {
                                    for (Map* umap : map)
                                        umap->setT(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                    i += 3;
                                }
                                else if (data[i] == "-textres")
                                {
                                    for (Map* umap : map)
                                        umap->setTextres(stoi(data[i + 1]));
                                    i++;
                                }
                                else if (data[i] == "-cc")
                                {
                                    if (data[i + 1] != "on" && data[i + 1] != "off")
                                        throw invalid_argument(lineError + to_string(lineNumber) + " for blendv value");

                                    for (Map* umap : map)
                                        umap->setCc(data[i + 1] == "on" ? true : false);
                                    i++;
                                }
                                else if (data[i] == "-boost")
                                {
                                    for (Map* umap : map)
                                        umap->setBoost(stof(data[i + 1]));
                                    i++;
                                }
                                else if (data[i] == "-imfchan")
                                {
                                    for (Map* umap : map)
                                    {
                                        umap->setImfchanrgb(vec3(stof(data[i + 1]), stof(data[i + 2]), stof(data[i + 3])));
                                        umap->setImfchanmlz(vec3(stof(data[i + 4]), stof(data[i + 5]), stof(data[i + 6])));
                                    }
                                    i += 6;
                                }
                                else
                                    throw invalid_argument(cmd + to_string(lineNumber) + " : " + dat0);
                            }
                        }
                    }
                }
            }
        }
        file.close();
#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] [loadMTLFile(const string& path) throw()] file success" << endl;
#endif
    }

    OBJFile::OBJFile()
        :    m_loadTime(0),
            m_name(""),
            m_objects()
    {
#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] [OBJFile()]..." << endl;
        cout << "[OBJFile " << m_name << "] [OBJFile()]...\tsuccess" << endl;
#endif
    }

    OBJFile::~OBJFile()
    {
#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] [~OBJFile()]...\n";
#endif
        for (Object* m : m_objects)
            if (m) delete m;
#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] [~OBJFile()]...\tsuccess" << endl;
#endif
    }

    void OBJFile::load(const string& path) throw()
    {
#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] load...\n";
#endif
        // calcule pour le temps de chargement
        milliseconds begin = duration_cast< milliseconds >(    system_clock::now().time_since_epoch());

        //netoyage des donnees
        for (Object* m : m_objects)
            if (m) delete m;

        //ouverture du fichier
        vector<string> filename = split(path, '.');
        if (filename[filename.size() - 1] != "obj")
            throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] can't read : " + filename[filename.size() - 1] + " extension");
        m_name = removenullptr(split(filename[filename.size() - 2],'/')).back();
        ifstream file(path, ios::in);
        if (!file)
            throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] can't open file : " + path);

        //code d'erreurs
        string symbol = "[OBJFile " + m_name + "] [load(const string& path) throw()] Unexpected symbol at the end of the line ";
        string value = "[OBJFile " + m_name + "] [load(const string& path) throw()] Wrong value at the line ";
        string invalideData = "[OBJFile " + m_name + "] [load(const string& path) throw() Missing value(s) at the line ";
        string lineError = "[OBJFile " + m_name + "] [load(const string& path) throw()] Unexpected symbol at the line ";

        //donneees
        vector<vec3> vertex(0);
        vector<vec3> normal(0);
        vector<vec2> textCoord(0);
        vector<vec3> index;
        string line;
        string mtllib = "";
        string usemtl = "";
        int lineNumber = 0;

        //parcourt du fichier
        while (getline(file, line, '\n'))
        {
            ++lineNumber;
            vector<string> data = removenullptr(split(line, ' '));
            if (data.size() > 0)
            {
                string dat0 = data[0];
                if (dat0 != "v" && dat0 != "vn" && dat0 != "vt" && dat0 != "f" && dat0 != "o" && dat0 != "g" && dat0 != "#" && dat0 != "usemtl" && dat0 != "mtllib" && dat0 != "s")
                    throw invalid_argument(lineError + to_string(lineNumber));
                if (dat0 == "v" || dat0 == "vn")
                {
                    if (data.size() < 4)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 4)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    vec3 val;
                    for(short i(1);i<=3; ++i)
                    {
                        try {
                            val[i - 1] = stof(data[i]);
                        }
                        catch (invalid_argument e){
                            throw invalid_argument(invalideData + to_string(lineNumber));
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
                    if (data.size() < 3)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 4)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    vec2 val;
                    for (short i(1); i <= 2; ++i)
                    {
                        try {
                            val[i - 1] = stof(data[i]);
                        }
                        catch (invalid_argument e) {
                            throw invalid_argument(invalideData + to_string(lineNumber));
                        }
                    }
                    textCoord.push_back(val);
                }
                else if (dat0 == "f")
                {
                    if (data.size() < 4)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 5)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    vec3 val;
                    short end = data.size() == 4 ? 1 : 3;
                    for (short k=0 ; k<end ; k+=2)
                    {
                        for (short i=0+k ; i<=2+k ; ++i)
                        {
                            vector<string> d = split(data[i%4+1], '/');
                            if (d.size() > 3)
                                throw invalid_argument(lineError + to_string(lineNumber));
                            if (d.size() == 1)
                            {
                                try {
                                    val[0] = stof(d[0]);
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument(invalideData + to_string(lineNumber));
                                }
                                val[1] = 0;
                                val[2] = 0;
                            }
                            else if (d.size() == 2)
                            {
                                try {
                                    float temp = stof(d[0]);
                                    val[0] = temp;
                                    temp = stof(d[1]);
                                    val[1] = temp;
                                    val[2] = 0;
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument(invalideData + to_string(lineNumber));
                                }
                            }
                            else if (d.size() == 3)
                            {
                                float temp;
                                try {
                                    temp = stof(d[0]);
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument(invalideData + to_string(lineNumber));
                                }
                                val[0] = temp;

                                if (d[1] == "")
                                    val[1] = 0;
                                else
                                {
                                    try {
                                        temp = stof(d[1]);
                                        val[1] = temp;
                                    }
                                    catch (invalid_argument e) {
                                        throw invalid_argument(invalideData + to_string(lineNumber));
                                    }
                                }

                                try {
                                    temp = stof(d[2]);
                                }
                                catch (invalid_argument e)
                                {
                                    throw invalid_argument(invalideData + to_string(lineNumber));
                                }
                                val[2] = temp;
                            }
                            else
                                throw invalid_argument(lineError + to_string(lineNumber));
                            index.push_back(val);
                        }
                    }
                }
                else if (dat0 == "o")
                {
                    if (data.size() < 2)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 2)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    if (index.size() != 0)
                    {
                        if (m_objects.size() > 0)
                        {
                            if (m_objects.back()->getGroups().size() > 0)
                            {
                                try {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                                }
                            }
                            else
                            {
                                m_objects.back()->addGroup("default_group");
                                try {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                                }
                            }
                        }
                        if (index.size() != 0)
                        {
                            m_objects.push_back(new Object("default_object"));
                            m_objects.back()->addGroup("default_group");
                            try {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch (invalid_argument e) {
                                throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                            }
                        }
                    }
                    m_objects.push_back(new Object(data[1]));
                }
                else if (dat0 == "g")
                {
                    if (data.size() > 2)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    if (data.size() == 2) {
                        if (m_objects.size() > 0)
                        {
                            if (m_objects.back()->getGroups().size() > 0)
                            {
                                if (index.size() != 0)
                                {
                                    try {
                                        push(&vertex, &normal, &textCoord, &index, &usemtl);
                                    }
                                    catch (invalid_argument e) {
                                        throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                                    }
                                }
                                m_objects.back()->addGroup(data[1]);
                            }
                            else
                            {
                                if (index.size() != 0)
                                {
                                    m_objects.back()->addGroup("default_group");
                                    try {
                                        push(&vertex, &normal, &textCoord, &index, &usemtl);
                                    }
                                    catch (invalid_argument e) {
                                        throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
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
                                try {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                                }
                            }
                            m_objects.push_back(new Object("default_object"));
                            m_objects.back()->addGroup(data[1]);
                        }
                    }
                }
                else if (dat0 == "mtllib")
                {
                    if (data.size() < 2)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 2)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    mtllib = data[1];
                    vector<string> lib = split(mtllib, '.');
                    if (lib.back() != "mtl")
                        throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] can't read " + lib[lib.size() - 1] + " extension for mtllib at line " + to_string(lineNumber));
                }
                else if (dat0 == "usemtl")
                {
                    if (data.size() < 2)
                        throw invalid_argument(invalideData + to_string(lineNumber));
                    if (data.size() > 2)
                        throw invalid_argument(symbol + to_string(lineNumber));
                    if (index.size() > 0)
                    {
                        if (m_objects.size() > 0)
                        {
                            if (m_objects.back()->getGroups().size() > 0)
                            {
                                try {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                                }
                                catch (invalid_argument e) {
                                    throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                                }
                            }
                            else
                            {
                                m_objects.back()->addGroup("default_group");
                                try {
                                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                                catch (invalid_argument e) {
                                    throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                                }
                            }
                        }
                        else {
                            m_objects.push_back(new Object("default_object"));
                            m_objects.back()->addGroup("default_group");
                            try {
                                push(&vertex, &normal, &textCoord, &index, &usemtl);
                            }
                            catch (invalid_argument e) {
                                throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                            }
                        }
                    }
                    usemtl = data[1];
                }
            }
        }

        //si rien n'a �t� push, on le fait ici
        if (index.size() > 0)
        {
            if (m_objects.size() > 0)
            {
                if (m_objects.back()->getGroups().size() > 0)
                {
                    try {
                        push(&vertex, &normal, &textCoord, &index, &usemtl);
                    }
                    catch (invalid_argument e) {
                        throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                    }
                }
                else
                {
                    m_objects.back()->addGroup("default_group");
                    try {
                        push(&vertex, &normal, &textCoord, &index, &usemtl);
                    }
                    catch (invalid_argument e) {
                        throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                    }
                }
            }
            else 
            {
                m_objects.push_back(new Object("default_group"));
                m_objects.back()->addGroup("default_group");
                try {
                    push(&vertex, &normal, &textCoord, &index, &usemtl);
                }
                catch (invalid_argument e) {
                    throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
                }
            }
        }

        //fermeture du fichier
        file.close();

#ifdef _DEBUG
        cout << "[OBJFile " << m_name << "] [load(const string& path) throw()]...\tsuccess" << endl;
#endif
        //chargement du fichier mtl
        if (mtllib != "")
        {
            filename = split(filename[0], '/');
            string res = "";
            for (int i(0); i < filename.size() - 1; i++)
                res += filename[i] + "/";
            try {
                loadMTLFile(res + mtllib);
            }
            catch (invalid_argument e) {
                throw invalid_argument("[OBJFile " + m_name + "] [load(const string& path) throw()] " + e.what());
            }
        }

        //temp de chargement du fichier
        milliseconds end = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        m_loadTime = (end - begin).count();
    }

    ostream& OBJFile::print(ostream& o) const
    {
        o << "[OBJFile " << m_name << "]";
        for (Object* ob : m_objects)
            o << "\t" << ob;
        return o;
    }

    const vector<Object*>& OBJFile::getObjects() const
    {
        return m_objects;
    }

    long long OBJFile::getLoadTime() const
    {
        return m_loadTime;
    }

    ostream& operator<<(ostream& o, const OBJFile& m)
    {
        m.print(o);
        return o;
    }

}
