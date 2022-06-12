// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "evidencia.h"

using namespace ::testing;


TEST(TestFirstTask, PrazdnyRegister_PocetPohladaviek) {
    Register t;
    t.premaz_subor();
	ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());
}

TEST(TestFirstTask, PrazdnyRegisterVypis_citajsubor) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Register je prazdny\n", t.citaj_subor());
}

TEST(TestFirstTask, PrazdnyRegisterHladaj_Podla_Veritela) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Register je prazdny\n", t.hladaj_podla_veritela("Slovnaft"));
}

TEST(TestFirstTask, Register_vloz_pohladavku_spravne) {
    Register t;
    ASSERT_EQ("Pohladavka uspesne vlozena\n", t.vloz_pohladavku("1\n"
                                                         "Roman Bozik\n"
                                                         "TatraBanka\n"
                                                         "95\n"
                                                         "25.8.2022"));
}
TEST(TestFirstTask, Register_vloz_pohladavku_nespravne_zle_ID) {
    Register t;
    ASSERT_EQ("ID pohladavky ma zly format", t.vloz_pohladavku("jedna\n"
                                                              "Roman Bozik\n"
                                                              "TatraBanka\n"
                                                              "90\n"
                                                              "25.8.2022"));
}
TEST(TestFirstTask, Kontrola_premazania) {
    Register t;
    t.vloz_pohladavku("2\n"
                      "PrimaBanka\n"
                      "AntonBerrolak\n"
                      "900\n"
                      "25.8.2025");
    ASSERT_EQ("2", t.pocet_vsetkych_pohladaviek());
    t.premaz_subor();
    ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());
}
TEST(TestFirstTask, Kontrola_opetovneho_pridania) {
    Register t;
    t.vloz_pohladavku("1\n"
                      "TatraBanka\n"
                      "RomanBozik\n"
                      "98\n"
                      "25.8.2022");
    ASSERT_EQ("1", t.pocet_vsetkych_pohladaviek());
}
TEST(TestFirstTask, Hladaj_podla_id_spravne) {
    Register t;
    t.vloz_pohladavku("2\n"
                      "InteractiveBrokers\n"
                      "AntonBerrolak\n"
                      "9800\n"
                      "25.8.2025");
    ASSERT_EQ("2\nInteractiveBrokers\nAntonBerrolak\n9800\n25.8.2025\n", t.hladaj_podla_id("2"));
}

TEST(TestFirstTask, Hladaj_podla_id_neexistujuce) {
    Register t;
    t.vloz_pohladavku("2\n"
                      "InteractiveBrokers\n"
                      "AntonBerrolak\n"
                      "9800\n"
                      "25.8.2025");
    ASSERT_EQ("Zaznam s takymto ID neexistuje", t.hladaj_podla_id("abeceda"));
}

TEST(TestFirstTask, Hladaj_podla_dlznika_neexistujuceho) {
    Register t;
    t.vloz_pohladavku("0105698751\n"
                      "XTB\n"
                      "JozkoSachovsky\n"
                      "800\n"
                      "31.8.2025");
    ASSERT_EQ("Zaznam s takymto dlznikom neexistuje", t.hladaj_podla_dlznika("XTB"));
}

TEST(TestFirstTask, Hladaj_podla_dlznika_existujuceho) {
    Register t;
    ASSERT_EQ("0105698751\nXTB\nJozkoSachovsky\n800\n31.8.2025\n", t.hladaj_podla_dlznika("JozkoSachovsky"));
}

TEST(TestFirstTask, Zly_den_v_datume) {
    Register t;
    ASSERT_EQ("Den musi byt z intervalu <1:31>\n", t.vloz_pohladavku("10121\nTatraBanka\nRomanBozik\n300\n0.3.2001"));
    ASSERT_EQ("Den musi byt z intervalu <1:31>\n", t.vloz_pohladavku("11111\nTatraBanka\nRomanBozik\n300\n32.3.2001"));
}

TEST(TestFirstTask, Zly_mesiac_v_datume) {
    Register t;
    ASSERT_EQ("Mesiac musi byt z intervalu <1:12>\n", t.vloz_pohladavku("10101\nTatraBanka\nRomanBozik\n300\n1.0.2001"));
    ASSERT_EQ("Mesiac musi byt z intervalu <1:12>\n", t.vloz_pohladavku("11111000\nTatraBanka\nRomanBozik\n300\n1.13.2001"));
}

TEST(TestFirstTask, Zly_rok_v_datume) {
    Register t;
    ASSERT_EQ("Rok nesmie byt mensi ako 1\n", t.vloz_pohladavku("10101\nTatraBanka\nRomanBozik\n300\n1.5.0"));
    ASSERT_EQ("Zly format datumu", t.vloz_pohladavku("10101\nTatraBanka\nRomanBozik\n300\n1.6.-5"));
}

TEST(TestFirstTask, Rovnake_ID_test) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Pohladavka uspesne vlozena\n", t.vloz_pohladavku("1\nTatraBanka\nRomanBozik\n300\n1.5.2020"));
    ASSERT_EQ("Pohladavka s tymto ID uz existuje\n", t.vloz_pohladavku("1\nTatraBanka\nRomanBozik\n300\n1.5.2020"));
}

TEST(TestFirstTask, Zlozeny_test) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());

    ASSERT_EQ("ID neuvedene\n", t.vloz_pohladavku("\nTatraBanka\nRomanBozik\n300\n23.3.2001"));
    ASSERT_EQ("Nepovoleny znak u veritela", t.vloz_pohladavku("5\n\b\nRomanBozik\n300\n23.3.2001"));
}
TEST(TestFirstTask, Zlozeny_test2) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Nepovoleny znak u dlznika", t.vloz_pohladavku("8\nTatraBanka\nRoman\rBozik\n300\n23.3.2001"));
    ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());
    ASSERT_EQ("Dlznik neuvedeny", t.vloz_pohladavku("5\nTatraBanka\n\n300\n23.3.2001"));
}

TEST(TestFirstTask, Zlozeny_test3) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Pohladavka uspesne vlozena\n", t.vloz_pohladavku("8\nTatraBanka\nRomanBozik\n300\n23.3.2001"));
    ASSERT_EQ("Dlznik neuvedeny", t.vloz_pohladavku("5\nTatraBanka\n\n300\n23.3.2001"));
    ASSERT_EQ("1", t.pocet_vsetkych_pohladaviek());
}

TEST(TestFirstTask, Zlozeny_test4_suma) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Suma ma zly format", t.vloz_pohladavku("8\nTatraBanka\nRomanBozik\n3O0\n23.3.2001"));
    ASSERT_EQ("Suma nie je uvedena", t.vloz_pohladavku("8\nTatraBanka\nRomanBozik\n\n23.3.2001"));
    ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());
}

TEST(TestFirstTask, Zlozeny_test5_datum) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Zly format datumu", t.vloz_pohladavku("8\nTatraBanka\nRomanBozik\n300\n3.2001"));
    ASSERT_EQ("Zly format datumu", t.vloz_pohladavku("8\nTatraBanka\nRomanBozik\n300\n23.3.xxx1"));
    ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());
}

TEST(TestFirstTask, CitajSubor) {
    Register t;
    t.premaz_subor();
    ASSERT_EQ("Register je prazdny\n", t.citaj_subor());
}

TEST(TestFirstTask, Vecsi_zapis) {
    Register t;
    t.premaz_subor();
    for (int i=0;i<20;i++){
        t.vloz_pohladavku(std::to_string(i)+"\n"+"Veritel"+"\n"+"Dlznik"+"\n"+std::to_string(i)+"\n"+std::to_string(1)+"."+std::to_string(1)+"."+std::to_string(2002));
    }
    ASSERT_EQ("20", t.pocet_vsetkych_pohladaviek());
}

TEST(TestFirstTask, Velky_zapis) {
    Register t;
    t.premaz_subor();
    for (int i=0;i<666;i++){
        t.vloz_pohladavku(std::to_string(i)+"\n"+"Veritel"+"\n"+"Dlznik"+"\n"+std::to_string(i)+"\n"+std::to_string(1)+"."+std::to_string(1)+"."+std::to_string(2022));
    }
    ASSERT_EQ("666", t.pocet_vsetkych_pohladaviek());
    t.premaz_subor();
    int k = 0;
    for (int i=0;i<1024;i++){
        k = k+i;
        t.vloz_pohladavku(std::to_string(i)+"\n"+"Veritel"+"\n"+"Dlznik"+"\n"+std::to_string(i)+"\n"+std::to_string(1)+"."+std::to_string(1)+"."+std::to_string(2022));
    }
    ASSERT_EQ("1024", t.pocet_vsetkych_pohladaviek());
    ASSERT_EQ(k, t.suma_vsetkych_pohladaviek());
    t.premaz_subor();
    ASSERT_EQ("0", t.pocet_vsetkych_pohladaviek());
    t.nacitaj_zo_suboru("evidencia_zaloha.txt");
    ASSERT_EQ("1024", t.pocet_vsetkych_pohladaviek());
    ASSERT_EQ(k, t.suma_vsetkych_pohladaviek());


}