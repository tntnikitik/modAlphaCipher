#include <UnitTest++/UnitTest++.h>
#include "headers/modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <stdexcept>
using namespace std;
struct KeyAB_fixture {
    modAlphaCipher * pointer;
    KeyAB_fixture()
    {
        pointer = new modAlphaCipher(L"АВ");
    }
    ~KeyAB_fixture()
    {
        delete pointer;
    }
};
SUITE(KeyTest)
{

    TEST(LargeLetters) {
        modAlphaCipher test(L"КОТЕЛ");
        CHECK(true);
    }
    TEST(LargeAndSmallLetters) {
        modAlphaCipher test(L"КОТопес");
        CHECK(true);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher test(L""), cipher_error);
    }
    TEST(Key_with_a_space) {
        CHECK_THROW(modAlphaCipher test(L"кото пес"), cipher_error);
    }
    TEST(Key_with_invalid_characters_number) {
        CHECK_THROW(modAlphaCipher test(L"кото2пес"), cipher_error);
    }
    TEST(Key_with_invalid_characters_special_character) {
        CHECK_THROW(modAlphaCipher test(L"кото.пес"), cipher_error);
    }
}
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring open_text = L"СЪЕШЬЖЕЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЧАЮ";
        wstring result_correct = L"СЮЕЬЬИЕЖЩЗЭФИЧМБГМИЧФТАПЦХЗУККХГУНОМДВВЭПЖЙЩАА";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
        
    }
    TEST_FIXTURE(KeyAB_fixture, SmallLetters) {
        wstring open_text = L"съешьжеещёэтихмягкихфранцузскихбулокдавыпейчаю";
        wstring result_correct = L"СЮЕЬЬИЕЖЩЗЭФИЧМБГМИЧФТАПЦХЗУККХГУНОМДВВЭПЖЙЩАА";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
        
    }
    TEST_FIXTURE(KeyAB_fixture,NumberInText) {
        wstring open_text = L"кора324мох";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSpecialSymbol) {
        wstring open_text = L"кора/мох";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace) {
        wstring open_text = L"кора мох";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }

}
SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring cipher_text = L"СЮЕЬЬИЕЖЩЗЭФИЧМБГМИЧФТАПЦХЗУККХГУНОМДВВЭПЖЙЩАА";
        wstring result_correct = L"СЪЕШЬЖЕЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЧАЮ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Smallletters) {
        wstring cipher_text = L"сюеььиежщзэфичмбгмичфтапцхзуккхгуномдввэпжйщаа";
        wstring result_correct = L"СЪЕШЬЖЕЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЧАЮ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture,LargeAndSmallLetters) {
        wstring cipher_text = L"ЗДраВстуЙТЕ";
        wstring result_correct = L"ЗВРЮВПТСЙРЕ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, EmptyText) {
        wstring cipher_text = L"";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithNumber) {
        wstring cipher_text = L"кора324мох";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSymbol) {
        wstring cipher_text = L"кора/мох";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace) {
        wstring cipher_text = L"Зкора мох";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
