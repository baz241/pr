#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "search_server.h"

using namespace std;

const double EPSILON = 1e-6;
/* Подставьте вашу реализацию класса SearchServer сюда */

/*
   Подставьте сюда вашу реализацию макросов
   ASSERT, ASSERT_EQUAL, ASSERT_EQUAL_HINT, ASSERT_HINT и RUN_TEST
*/

// -------- Начало модульных тестов поисковой системы ----------

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const std::string content = "cat in the city"s;
    const std::vector<int> ratings = { 1, 2, 3 };
    // Сначала убеждаемся, что поиск слова, не входящего в список стоп-слов,
    // находит нужный документ
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("in"s);
        ASSERT(found_docs.size() == 1);
        const Document& doc0 = found_docs[0];
        ASSERT(doc0.id == doc_id);
    }

    // Затем убеждаемся, что поиск этого же слова, входящего в список стоп-слов,
    // возвращает пустой результат
    {
        SearchServer server;
        server.SetStopWords("in the"s);
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        ASSERT(server.FindTopDocuments("in"s).empty());
    }
}

void TestDocumentExistence()
{
    const int doc_id = 3;
    const std::string content = "cat in the city"s;
    const std::vector<int> ratings = { 1, 2, 3 };

    SearchServer server;
    server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
    
    
    {
        const auto found_docs = server.FindTopDocuments("cat"s);
        ASSERT(found_docs.size() == 1);
        ASSERT(found_docs[0].id == 3);
    }

    {
        const auto found_docs = server.FindTopDocuments("dog"s);
        ASSERT(found_docs.size() == 0);
    }
}

void TestMinusWordsExclusion()
{
    const int doc_id = 3;
    const std::string content = "cat in the city"s;
    const std::vector<int> ratings = { 1, 2, 3 };

    SearchServer server;
    server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);

    // Проверяем, что поиск по-прежнему работает для документов с минус-словами
    {
        const auto found_docs = server.FindTopDocuments("cat"s);
        ASSERT(found_docs.size() == 1);
        ASSERT(found_docs[0].id == 3);
    }

    // Проверяем, что минус-слова исключаются
    {
        const auto found_docs = server.FindTopDocuments("-city"s);
        ASSERT(found_docs.size() == 0);
    }
}

void TestDocumentMatching()
{
    const int doc_id = 3;
    const std::string content = "cat in the city"s;
    const std::vector<int> ratings = { 1, 2, 3 };

    SearchServer server;
    server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);

    {
        const std::string query = "cat";
        const auto [matched_words, status] = server.MatchDocument(query, doc_id);

        ASSERT(matched_words.size() == 1);
        ASSERT(matched_words[0] == "cat");
    }

    {
        const std::string query = "cat -city";
        const auto [matched_words, status] = server.MatchDocument(query, doc_id);

        ASSERT(matched_words.size() == 0);
    }

}

void TestAverageRating()
{
    const int doc_id = 3;
    const std::string content = "cat in the city"s;
    const std::vector<int> ratings = { 1, 2, 3 };

    SearchServer server;
    server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);

    const std::string query = "cat";
    auto docs = server.FindTopDocuments(query);
    
    ASSERT(docs[0].rating == 2);
}

void TestRelevanceSort()
{
    SearchServer search_server;
    search_server.SetStopWords("and in on"s);
    search_server.AddDocument(0, "white cat and nice collar"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "fluffy cat fluffy tail"s, DocumentStatus::IRRELEVANT, { 7, 2, 7 });
    search_server.AddDocument(2, "well-groomed dog expressive eyes"s, DocumentStatus::REMOVED, { 5, -12, 2, 1 });
    search_server.AddDocument(3, "well-groomed starling evgeny"s, DocumentStatus::BANNED, { 9 });

    const auto& documents = search_server.FindTopDocuments("fluffy well-groomed cat"s);

    ASSERT(documents.size() != 0);

    for (size_t i = 1; i < documents.size() - 1; ++i)
        ASSERT(documents[i].relevance > documents[i - 1].relevance);

}

void TestStatusFilter()
{
    SearchServer search_server;
    search_server.AddDocument(0, "white cat and nice collar"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "fluffy cat fluffy tail"s, DocumentStatus::IRRELEVANT, { 7, 2, 7 });
    search_server.AddDocument(2, "well-groomed cat expressive eyes"s, DocumentStatus::REMOVED, { 5, -12, 2, 1 });
    search_server.AddDocument(3, "well-groomed cat evgeny"s, DocumentStatus::BANNED, { 9 });

    {
        const auto& documents = search_server.FindTopDocuments("cat"s, DocumentStatus::BANNED);

        ASSERT(documents.size() == 1);
        ASSERT(documents[0].id == 3);
    }

    {
        const auto& documents = search_server.FindTopDocuments("cat"s, DocumentStatus::IRRELEVANT);

        ASSERT(documents.size() == 1);
        ASSERT(documents[0].id == 1);
    }

    {
        const auto& documents = search_server.FindTopDocuments("cat"s, DocumentStatus::ACTUAL);

        ASSERT(documents.size() == 1);
        ASSERT(documents[0].id == 0);
    }
}

void TestRelevancyAccuracy()
{
    SearchServer search_server;
    search_server.SetStopWords("and in on"s);
    search_server.AddDocument(0, "white cat and nice collar"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "fluffy cat fluffy tail"s, DocumentStatus::ACTUAL, { 7, 2, 7 });

    const double relevance_id0 = 0.173287;
    const double relevance_id1 = 0.866434;

    const auto& docs = search_server.FindTopDocuments("fluffy well-groomed cat"s);

    ASSERT(docs.size() == 2);
    ASSERT(docs[0].relevance - relevance_id1 < EPSILON);
    ASSERT(docs[1].relevance - relevance_id0 < EPSILON);
}

void TestUserPredicate()
{
    SearchServer search_server;
    search_server.SetStopWords("and in on"s);
    search_server.AddDocument(0, "white cat and nice collar"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "fluffy cat fluffy tail"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "well-groomed dog expressive eyes"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });
    search_server.AddDocument(3, "well-groomed starling evgeny"s, DocumentStatus::BANNED, { 9 });

    {
        const auto& documents = search_server.FindTopDocuments("fluffy well-groomed cat"s,
            [](int document_id, DocumentStatus status, int rating) { return status == DocumentStatus::BANNED; });
        
        ASSERT(documents.size() == 1);
        ASSERT(documents[0].id == 3);
    }

    {
        const auto& documents = search_server.FindTopDocuments("fluffy well-groomed cat"s,
            [](int document_id, DocumentStatus status, int rating) { return document_id % 2 == 0; });

        ASSERT(documents.size() == 2);
        ASSERT(documents[0].id == 0);
        ASSERT(documents[1].id == 2);
    }

}

/*
Разместите код остальных тестов здесь
*/

// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
    // Поддержка стоп-слов
    RUN_TEST(TestExcludeStopWordsFromAddedDocumentContent);
    RUN_TEST(TestDocumentExistence);
    RUN_TEST(TestMinusWordsExclusion);
    RUN_TEST(TestDocumentMatching);
    RUN_TEST(TestRelevanceSort);
    RUN_TEST(TestAverageRating);
    RUN_TEST(TestStatusFilter);
    RUN_TEST(TestRelevancyAccuracy);
    RUN_TEST(TestUserPredicate);
    // Не забудьте вызывать остальные тесты здесь
}

// --------- Окончание модульных тестов поисковой системы -----------

int main() {
    TestSearchServer();
    // Если вы видите эту строку, значит все тесты прошли успешно
    cout << "Search server testing finished"s << endl;
}