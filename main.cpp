#include "evidencia.h"

int main() {
    Register t;

    std::cout<<"***Register dlznikov***\n";
    std::cout<<"1. Zobrazit cely register\n";
    std::cout<<"2. Hladaj dlznika\n";
    std::cout<<"3. Hladaj veritela\n";
    std::cout<<"4. Hladaj podla ID\n";
    std::cout<<"5. Vloz pohladavku\n";
    std::cout<<"6. Pocet vsetkych pohladaviek\n";
    std::cout<<"7. Sucet vsetkych pohladaviek\n";
    std::cout<<"8. Zmaz register\n";
    std::cout<<"9. Vloz register\n";
    std::cout<<"0. Odchod\n";
    while ( true )
    {
        std::string input;
        getline( std::cin, input );



        if ( input == "exit" ){
            std::cout << "Rad Vam posluzim aj nabuduce." << std::endl;
            break;
        }
        else if ( input == "menu" )
        {
            std::cout<<"\n";
            std::cout<<"1. Zobrazit cely register\n";
            std::cout<<"2. Hladaj dlznika\n";
            std::cout<<"3. Hladaj veritela\n";
            std::cout<<"4. Hladaj podla ID\n";
            std::cout<<"5. Vloz pohladavku\n";
            std::cout<<"6. Pocet vsetkych pohladaviek\n";
            std::cout<<"7. Sucet vsetkych pohladaviek\n";
            std::cout<<"8. Zmaz register\n";
            std::cout<<"9. Vloz register\n";
            std::cout<<"0. Odchod\n";
        }
        else if(input == "1"){
            std::cout << t.citaj_subor();
        }
        else if(input == "2"){
            std::cout << "\nZadaj cele meno dlznika\n";
            std::string strid;
            getline( std::cin, strid );
            std::cout << t.hladaj_podla_dlznika(strid);
        }
        else if(input == "3"){
            std::cout << "\nZadaj veritela\n";
            std::string strid;
            getline( std::cin, strid );
            std::cout << t.hladaj_podla_veritela(strid);
        }
        else if(input == "4"){
            std::cout << "\nZadaj ID pohladavky\n";
            std::string strid;
            getline( std::cin, strid );
            std::cout << t.hladaj_podla_id(strid);
        }
        else if(input == "5"){
            std::cout << "\nZadaj ID pohladavky\n";
            std::string strid;
            std::string hotovo;
            getline( std::cin, strid );
            hotovo+=strid+"\n";
            std::cout << "\nZadaj veritela\n";
            getline( std::cin, strid );
            hotovo+=strid+"\n";
            std::cout << "\nZadaj dlznika\n";
            getline( std::cin, strid );
            hotovo+=strid+"\n";
            std::cout << "\nZadaj aktualny dlh\n";
            getline( std::cin, strid );
            hotovo+=strid+"\n";
            std::cout << "\nZadaj dobu splatnosti\n";
            getline( std::cin, strid );
            hotovo+=strid+"\n";
            std::cout << t.vloz_pohladavku(hotovo)+"\n";
        }
        else if(input == "6"){
            std::cout << "\nPocet vsetkych pohladaviek v registri: "+t.pocet_vsetkych_pohladaviek()+"\n";

        }
        else if(input == "7"){
            std::cout << "\nSucet vsetkych pohladaviek v registri: "+std::to_string(t.suma_vsetkych_pohladaviek())+"\n";

        }
        else if(input == "8"){
            std::cout << "Pre vymaz registra potvrdte heslom 'vYmaZaT'\n";
            std::string strid;
            getline( std::cin, strid );
            if(strid =="vYmaZaT") std::cout << t.premaz_subor()+"\n";
            else std::cout <<"Zle zadane heslo, stornujem operaciu";
        }
        else if(input == "9"){
            std::cout << "Vlozte nazov suboru s príponou\n";
            std::string strid;
            getline( std::cin, strid );
            t.nacitaj_zo_suboru(strid);
        }
        else if(input == "0"){
            std::cout << "Rad Vam posluzim aj nabuduce." << std::endl;
            break;
        }
        else std::cout <<"Bohuzial som Vam nerozumel. Skuste prikaz zopakovat\n";

    }


}