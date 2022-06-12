#include <iostream>
#include <iomanip>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "evidencia.h"
void Register::push(const std::string ky)
{
    Node* node = new Node;
    node->key = ky;
    node->next = head;
    head = node;
}
void Register::deleteAllNodes(Node** head_ref) {
    Node* current = *head_ref;
    Node* next;
    while (current != nullptr){
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = nullptr;
}
std::uintmax_t Velkost_suboru(const std::string& subor){
    std::ifstream soubor(subor);
    if(soubor.fail()) {
        std::cout <<"Subor s tymto nazvom neexistuje !\n";
        return -1;
    }
    return std::filesystem::file_size(subor);
}

std::string uhladenie_textu(std::string str,std::string::size_type i){
    std::string ukoncovac = "\n";
    std::string er = "\r";
    std::string te = "\t";
    std::string be = "\b";
    std::string ve = "\v";
    std::string nula = "\0";
    if (i != std::string::npos)
        str.erase(i, ukoncovac.length());
    i = str.find(er);
    if (i != std::string::npos)
        str.erase(i, er.length());
    i = str.find(te);
    if (i != std::string::npos)
        str.erase(i, te.length());
    i = str.find(be);
    if (i != std::string::npos)
        str.erase(i, be.length());
    i = str.find(ve);
    if (i != std::string::npos)
        str.erase(i, ve.length());
    i = str.find(nula);
    if (i != std::string::npos)
        str.erase(i, nula.length());
    return str;
}


void Register::inicializacia(){
    if(test_suboru() == false) {
        std::ofstream myfile;
        myfile.open ("evidencia.txt");
        myfile.close();
    }
    deleteAllNodes(&head);
    IDcka.clear();
    velkost_suboru = Velkost_suboru("evidencia.txt");
    std::ifstream infile;
    std::string str;
    std::string ukoncovac = "\n";
    std::string hotovo="";
    int k = 0;
    infile.open("evidencia.txt");
    if (infile) {
        while (std::getline(infile, str)){
            std::string::size_type i = str.find(ukoncovac);
            str = uhladenie_textu(str,i);
            if(i==0) IDcka.push_back(str);
            if (k==0||k==1||k==2||k==3||k==4){
                hotovo += str + "\n";
            }
            k = k+1;
            if (k==5)push(hotovo);
            if (k==5)hotovo="";
            if (k==5) k=0;
        }
    }
    else {
        push("Nepodarilo sa precitat subor\n");
    }
    infile.close();
}

bool Register::test_suboru()const {
    const std::string name = "evidencia.txt";
    std::ifstream f(name.c_str());
    return f.good();
}
Register::Register() {
    inicializacia();
}
std::string Register::vloz_pohladavku(const std::string &pohladavka) {
    std::istringstream iss(pohladavka);
    std::string str;
    std::string id;
    std::string veritel;
    std::string dlznik;
    std::string suma;
    std::string splatnost;
    int k = 0;
    while (std::getline(iss, str))
    {
        if (k==0) {
            if(!(str.find_first_not_of( "0123456789" ) == std::string::npos)) return"ID pohladavky ma zly format";
            if (str.empty()) return"ID neuvedene\n";
            if (std::find(IDcka.begin(), IDcka.end(), str) != IDcka.end())
            {
                return "Pohladavka s tymto ID uz existuje\n";
            }
            id = str;
        }
        else if (k==1) {
            if (str.find("\n") != std::string::npos ||str.find("\t") != std::string::npos||str.find("\r") != std::string::npos||str.find("\b") != std::string::npos||str.find("\v") != std::string::npos) {
                return"Nepovoleny znak u veritela";
            }
            if (str.empty()) return"Veritel neuvedeny";
            if (std::any_of(str.begin(), str.end(), ::isdigit)) return"Cislo v mene veritela";
            veritel = str;
        }
        else if (k==2) {
            if (str.find("\n") != std::string::npos ||str.find("\t") != std::string::npos||str.find("\r") != std::string::npos||str.find("\b") != std::string::npos||str.find("\v") != std::string::npos) {
                return"Nepovoleny znak u dlznika";
            }
            if (str.empty()) return"Dlznik neuvedeny";
            if (std::any_of(str.begin(), str.end(), ::isdigit)) return"Cislo v mene dlznika";
            dlznik = str;
        }
        else if (k==3) {
            if(str.find_first_not_of("0123456789") != std::string::npos) return"Suma ma zly format";
            if (str.empty()) return"Suma nie je uvedena";
            suma = str;
        }
        else if (k==4) {
            std::istringstream izz(str);
            char dash;
            int den,mesiac,rok;
            den = mesiac = rok =0;
            if (izz >> den >> dash) {
                if (dash != '.') return"Zly format datumu";
                if (izz >> mesiac >> dash) {
                    if (dash != '.') return"Zly format datumu";
                    if (izz >> rok) {
                        if(!(std::to_string(den).find_first_not_of( "0123456789" ) == std::string::npos)) return"Zly format datumu";
                        if(!(std::to_string(mesiac).find_first_not_of( "0123456789" ) == std::string::npos)) return"Zly format datumu";
                        if(!(std::to_string(rok).find_first_not_of( "0123456789" ) == std::string::npos)) return"Zly format datumu";
                        if(den<1 || den>31) return"Den musi byt z intervalu <1:31>\n";
                        if(mesiac<1 || mesiac>12) return"Mesiac musi byt z intervalu <1:12>\n";
                        if(rok<1) return"Rok nesmie byt mensi ako 1\n";
                        splatnost = std::to_string(den)+"."+std::to_string(mesiac)+"."+std::to_string(rok);
                    }
                }
            }

            if (izz.fail()) {
                return"Zly format datumu";
            }

        }
        else if(k==5) break;
        k = k+1;
    }


    std::ofstream outfile;
    if(velkost_suboru!= Velkost_suboru("evidencia.txt")){
        std::cout << "!!!Obsah registra sa neočakávane zmenil!!! Pre pokračovanie, napíšte 'ano',pre zrusenie akcie stlacte akukolvek inu klavesu" << std::endl;
        while ( true )
        {

            std::string input;
            getline( std::cin, input );

            if ( input == "ano" )
            {
                inicializacia();
                break;
            }
            else{
                std::cout<< "Rusim vlozenie pohladavky";
                return "Chyba pri zapise";


            }
        }
    }
    outfile.open("evidencia.txt", std::ios_base::app); // append instead of overwrite
    if (outfile){
        outfile << id+"\n"+veritel+"\n"+dlznik+"\n"+suma+"\n"+splatnost+"\n";
        push(id+"\n"+veritel+"\n"+dlznik+"\n"+suma+"\n"+splatnost+"\n");
        IDcka.push_back(id);
        velkost_suboru = Velkost_suboru("evidencia.txt");
    }
    else return "Chyba pri zapise";
    outfile.close();
    velkost_suboru = Velkost_suboru("evidencia.txt");
    return "Pohladavka uspesne vlozena\n";
}
std::string Register::citaj_subor() const{
    std::string hotovo="";
    Node* ptr = head;
    while (ptr != nullptr)
    {
        hotovo+= ptr->key;
        ptr = ptr->next;
    }
    if (hotovo.empty()) return "Register je prazdny\n";
    return hotovo;
}


std::string Register::premaz_subor() {
    std::ofstream ofk;
    ofk.open("evidencia_zaloha.txt", std::ofstream::out | std::ofstream::trunc);
    ofk.close();
    std::ofstream outfile;
    outfile.open("evidencia_zaloha.txt", std::ios_base::app);
    if (outfile){
        std::ifstream infile;
        infile.open("evidencia.txt");
        if(infile){
            std::string content = "";
            int i;
            for(i=0 ; infile.eof()!=true ; i++) content += infile.get();
            content.erase(content.end()-1);
            infile.close();
            outfile << content;
            outfile.close();
        }
        else return "Chyba pri citani originalu";
    }
    else return "Chyba pri zapise zalohy";
    std::ofstream ofs;
    ofs.open("evidencia.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    inicializacia();
    velkost_suboru = Velkost_suboru("evidencia.txt");
    return "Register uspesne premazany";
}

std::string Register::hladaj_podla_id(const std::string &hladane_id)const {
        std::string text = citaj_subor();
        if (text=="Nepodarilo sa precitat subor\n" || text.empty()) return "Nepodarilo sa precitat subor\n";
        if (text=="Register je prazdny\n" ) return "Register je prazdny\n";
        std::istringstream iss(text);
        int k = 0;
        std::string str;
        std::string hotovo;
        bool nasiel = false;
        while (std::getline(iss, str))
        {
            if(k==0 and str==hladane_id) nasiel = true;
            if ((k==0||k==1||k==2||k==3||k==4) and nasiel) hotovo+=str+"\n";
            k = k+1;
            if (k==5 and nasiel) break;
            if (k==5) k=0;

        }
        if (hotovo.empty()) return "Zaznam s takymto ID neexistuje";
        return hotovo;
}
std::string Register::hladaj_podla_veritela(const std::string &hladane_id) const{
    std::string text = citaj_subor();
    if (text=="Nepodarilo sa precitat subor\n") return "Nepodarilo sa precitat subor\n";
    if (text=="Register je prazdny\n" || text.empty()) return "Register je prazdny\n";
    std::istringstream iss(text);
    int k = 0;
    std::string str;
    std::string hotovo;
    std::string zaloha_id;
    bool nasiel = false;
    while (std::getline(iss, str))
    {
        if(k==0) zaloha_id = str;
        if(k==1 and str==hladane_id) nasiel = true;
        if(k==1 and str==hladane_id) hotovo+=zaloha_id+"\n";
        if ((k==1||k==2||k==3||k==4) and nasiel) hotovo+=str+"\n";
        k = k+1;
        if (k==5 and nasiel) nasiel=false;
        if (k==5) k=0;

    }
    if (hotovo.empty()) return "Zaznam s takymto veritelom neexistuje";
    return hotovo;
}

std::string Register::hladaj_podla_dlznika(const std::string &hladane_id)const {
    std::string text = citaj_subor();
    if (text=="Nepodarilo sa precitat subor\n") return "Nepodarilo sa precitat subor\n";
    if (text=="Register je prazdny\n" || text.empty()) return "Register je prazdny\n";
    std::istringstream iss(text);
    int k = 0;
    std::string str;
    std::string hotovo;
    std::string zaloha_id;
    std::string zaloha_veritel;
    bool nasiel = false;
    while (std::getline(iss, str))
    {
        if(k==0) zaloha_id = str;
        if(k==1) zaloha_veritel = str;
        if(k==2 and str==hladane_id) nasiel = true;
        if(k==2 and str==hladane_id) hotovo+=zaloha_id+"\n"+zaloha_veritel+"\n";
        if ((k==2||k==3||k==4) and nasiel) hotovo+=str+"\n";
        k = k+1;
        if (k==5 and nasiel) nasiel=false;
        if (k==5) k=0;

    }
    if (hotovo.empty()) return "Zaznam s takymto dlznikom neexistuje";
    return hotovo;
}
std::string Register::pocet_vsetkych_pohladaviek() const{
    const std::string text = citaj_subor();
    if (text=="Nepodarilo sa precitat subor\n") return "Nepodarilo sa precitat subor\n";
    if (text=="Register je prazdny\n" || text.empty()) return "0";
    std::istringstream iss(text);
    int k = 0;
    std::string hotovo;
    std::string str;
    int pocet = 0;
    while (std::getline(iss, str))
    {
        if (k==0) pocet= pocet +1;
        k = k+1;
        if (k==5) k=0;

    }
    return std::to_string(pocet);
}

int Register::suma_vsetkych_pohladaviek() const{
    const std::string text = citaj_subor();
    if (text=="Nepodarilo sa precitat subor\n") return -1;
    if (text=="Register je prazdny\n" || text.empty()) return 0;
    std::istringstream iss(text);
    int k = 0;
    std::string hotovo;
    std::string str;
    int pocet = 0;
    while (std::getline(iss, str))
    {
        if (k==3) pocet+= std::stoi( str );
        k = k+1;
        if (k==5) k=0;

    }
    return pocet;
}
void Register::nacitaj_zo_suboru(const std::string& nazov_suboru){
    velkost_suboru = Velkost_suboru(nazov_suboru);
    if(velkost_suboru == -1) return;
    if(test_suboru() == false) {
        std::ofstream myfile;
        myfile.open (nazov_suboru);
        myfile.close();
    }
    deleteAllNodes(&head);
    IDcka.clear();
    std::ifstream infile;
    std::string str;
    std::string ukoncovac = "\n";
    std::string hotovo="";
    int k = 0;
    infile.open(nazov_suboru);
    if (infile) {
        while (std::getline(infile, str)){
            std::string::size_type i = str.find(ukoncovac);
            str = uhladenie_textu(str,i);
            if(i==0) IDcka.push_back(str);
            if (k==0||k==1||k==2||k==3||k==4){
                hotovo += str + "\n";
            }
            k = k+1;
            if (k==5)push(hotovo);
            if (k==5)hotovo="";
            if (k==5) k=0;
        }
    }
    else std::cout<<"Neznama chyba pri citani suboru!";

    infile.close();
    std::ofstream ofk;
    ofk.open("evidencia.txt", std::ofstream::out | std::ofstream::trunc);
    ofk.close();
    std::ofstream outfile;
    outfile.open("evidencia.txt", std::ios_base::app);
    if (outfile){
        std::ifstream infile;
        infile.open(nazov_suboru);
        if(infile){
            std::string content = "";
            int i;
            for(i=0 ; infile.eof()!=true ; i++) content += infile.get();
            content.erase(content.end()-1);
            infile.close();
            outfile << content;
            outfile.close();
        }
        else {std::cout<< "Chyba pri citani originalu";return;}
    }
    else {std::cout<< "Chyba pri zapise do registra";return;}
    velkost_suboru = Velkost_suboru("evidencia.txt");
    std::cout <<"Novy register uspesne vlozeny\n";
}