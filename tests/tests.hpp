//
// Created by kadius on 02.12.23.
//

#ifndef URL_TESTS_HPP
#define URL_TESTS_HPP

#include <gtest/gtest.h>
#include "../src/parser.hpp"


TEST(PARSER_TESTS, PROTOCOL_PARSING) {

    std::string URL = "https://www.youtube.com/watch?v=xm3YgoEiEDc"; //// <- check this out :D
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "https");
    ASSERT_EQ(result["host"], "www.youtube.com");
    ASSERT_EQ(result["port"], "80");
    ASSERT_EQ(result["path"], "watch");
    ASSERT_EQ(result["searchpart"], "v=xm3YgoEiEDc");
}

TEST(PARSER_TESTS, HTTPS_PARSING) {

    std::string URL = "https://www.youtube.com:80/watch?v=xm3YgoEiEDc";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "https");
    ASSERT_EQ(result["host"], "www.youtube.com");
}

TEST(PARSER_TESTS, HTTPS_PARSING2) {

    std::string URL = "https://www.youtube.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "https");
    ASSERT_EQ(result["host"], "www.youtube.com");
    ASSERT_EQ(result["port"], "80");
}

TEST(PARSER_TESTS, HTTPS_PARSING3) {

    std::string URL = "https://www.youtube.com:69";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "https");
    ASSERT_EQ(result["host"], "www.youtube.com");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, HTTPS_PARSING4) {

    std::string URL = "https://www.youtube.com:69/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "https");
    ASSERT_EQ(result["host"], "www.youtube.com");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, HTTPS_PARSING5) {

    std::string URL = "https://www.youtube.com/watch?v=niqrrmev4mA";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "https");
    ASSERT_EQ(result["host"], "www.youtube.com");
    ASSERT_EQ(result["port"], "80");
    ASSERT_EQ(result["path"], "watch");
    ASSERT_EQ(result["searchpart"], "v=niqrrmev4mA");
}

TEST(PARSER_TESTS, GOPHER_PARSING1) {

    std::string URL = "gopher://www.LUL.com/0a_gopher_selector";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "gopher");
    ASSERT_EQ(result["host"], "www.LUL.com");
    ASSERT_EQ(result["port"], "70");
    ASSERT_EQ(result["path"], "0a_gopher_selector");
}

TEST(PARSER_TESTS, NNTP_PARSING1) {

    std::string URL = "nntp://news.server.org/example.group.this/12345";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "nntp");
    ASSERT_EQ(result["host"], "news.server.org");
    ASSERT_EQ(result["port"], "119");
    ASSERT_EQ(result["newsgroup"], "example.group.this");
    ASSERT_EQ(result["article"], "12345");
}

TEST(PARSER_TESTS, NNTP_PARSING2) {

    std::string URL = "nntp://news.server.org:42/example.group.this/12345";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "nntp");
    ASSERT_EQ(result["host"], "news.server.org");
    ASSERT_EQ(result["port"], "42");
    ASSERT_EQ(result["newsgroup"], "example.group.this");
    ASSERT_EQ(result["article"], "12345");
}

TEST(PARSER_TESTS, WAIS_PARSING1) {

    std::string URL = "wais://localhost:69/DB";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "wais");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, WAIS_PARSING2) {

    std::string URL = "wais://localhost/DB";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "wais");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "210");
}

TEST(PARSER_TESTS, WAIS_PARSING3) {

    std::string URL = "wais://localhost/DB?queryquery";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "wais");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "210");
    ASSERT_EQ(result["searchpart"], "queryquery");
}

TEST(PARSER_TESTS, WAIS_PARSING4) {

    std::string URL = "wais://localhost/DB/typetype/pathpath";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "wais");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "210");
    ASSERT_EQ(result["wtype"], "typetype");
    ASSERT_EQ(result["wpath"], "pathpath");
}

TEST(PARSER_TESTS, FILES_PARSING1) {

    std::string URL = "file://vms.host.edu/disk$user/my/notes/note12345.txt";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "file");
    ASSERT_EQ(result["host"], "vms.host.edu");
    ASSERT_EQ(result["path"], "disk$user/my/notes/note12345.txt");
}

TEST(PARSER_TESTS, PROSPERO_PARSING1) {

    std::string URL = "prospero://localhost:69/namename;a=42";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "prospero");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "69");
    ASSERT_EQ(result["hsoname"], "namename");
    ASSERT_EQ(result["parameters"], "a=42");
}

TEST(PARSER_TESTS, PROSPERO_PARSING2) {

    std::string URL = "prospero://localhost/namename;a=42";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "prospero");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "1525");
    ASSERT_EQ(result["hsoname"], "namename");
    ASSERT_EQ(result["parameters"], "a=42");
}

TEST(PARSER_TESTS, PROSPERO_PARSING3) {

    std::string URL = "prospero://localhost//namename;a=42";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "prospero");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "1525");
    ASSERT_EQ(result["hsoname"], "/namename");
    ASSERT_EQ(result["parameters"], "a=42");
}

TEST(PARSER_TESTS, PROSPERO_PARSING4) {

    std::string URL = "prospero://localhost//namename";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "prospero");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "1525");
    ASSERT_EQ(result["hsoname"], "/namename");
    ASSERT_EQ(result["parameters"], "");
}

TEST(PARSER_TESTS, FTP_PARSING1) {

    std::string URL = "ftp://localhost";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["host"], "localhost");
}

TEST(PARSER_TESTS, FTP_PARSING2) {

    std::string URL = "ftp://localhost/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["host"], "localhost");
}

TEST(PARSER_TESTS, FTP_PARSING3) {

    std::string URL = "ftp://localhost/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["host"], "localhost");
}

TEST(PARSER_TESTS, FTP_PARSING4) {

    std::string URL = "ftp://localhost:69";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, FTP_PARSING5) {

    std::string URL = "ftp://localhost:69/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["host"], "localhost");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, FTP_PARSING6) {

    std::string URL = "ftp://@host.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "");
    ASSERT_EQ(result["password"], "");
}

TEST(PARSER_TESTS, FTP_PARSING7) {

    std::string URL = "ftp://Kadius@host.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "Kadius");
    ASSERT_EQ(result["password"], "");
}

TEST(PARSER_TESTS, FTP_PARSING8) {

    std::string URL = "ftp://Kadius:@host.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "Kadius");
    ASSERT_EQ(result["password"], "EMPTY");
}

TEST(PARSER_TESTS, FTP_PARSING9) {

    std::string URL = "ftp://@host.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "");
    ASSERT_EQ(result["password"], "");
}

TEST(PARSER_TESTS, FTP_PARSING10) {

    std::string URL = "ftp://KadiusLunarflame:Mellon@host.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "KadiusLunarflame");
    ASSERT_EQ(result["password"], "Mellon");
}

TEST(PARSER_TESTS, FTP_PARSING11) {

    std::string URL = "ftp://ftp.funet.fi/pub/standards/RFC/rfc959.txt";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "");
    ASSERT_EQ(result["password"], "");
    ASSERT_EQ(result["host"], "ftp.funet.fi");
    ASSERT_EQ(result["path"], "pub/standards/RFC/rfc959.txt");
}

TEST(PARSER_TESTS, FTP_PARSING12) {

    std::string URL = "ftp://@ftp.funet.fi/pub/standards/RFC/rfc959.txt";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "");
    ASSERT_EQ(result["password"], "");
    ASSERT_EQ(result["host"], "ftp.funet.fi");
    ASSERT_EQ(result["path"], "pub/standards/RFC/rfc959.txt");
    ASSERT_EQ(result["port"], "21");
}

TEST(PARSER_TESTS, FTP_PARSING13) {

    std::string URL = "ftp://KadiusLunarflame:Mellon@ftp.funet.fi/pub/standards/RFC/rfc959.txt";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "KadiusLunarflame");
    ASSERT_EQ(result["password"], "Mellon");
    ASSERT_EQ(result["host"], "ftp.funet.fi");
    ASSERT_EQ(result["path"], "pub/standards/RFC/rfc959.txt");
    ASSERT_EQ(result["port"], "21");
}

TEST(PARSER_TESTS, FTP_PARSING14) {

    std::string URL = "ftp://KadiusLunarflame:Mellon@ftp.funet.fi:69/pub/standards/RFC/rfc959.txt";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "KadiusLunarflame");
    ASSERT_EQ(result["password"], "Mellon");
    ASSERT_EQ(result["host"], "ftp.funet.fi");
    ASSERT_EQ(result["path"], "pub/standards/RFC/rfc959.txt");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, FTP_PARSING15) {

    std::string URL = "ftp://KadiusLunarflame:@ftp.funet.fi:69/pub/standards/RFC/rfc959.txt";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "ftp");
    ASSERT_EQ(result["user"], "KadiusLunarflame");
    ASSERT_EQ(result["password"], "EMPTY");
    ASSERT_EQ(result["host"], "ftp.funet.fi");
    ASSERT_EQ(result["path"], "pub/standards/RFC/rfc959.txt");
    ASSERT_EQ(result["port"], "69");
}

TEST(PARSER_TESTS, TELNET_PARSING1) {

    std::string URL = "telnet://KadiusLunarflame:Mellon@srv.lul/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "telnet");
    ASSERT_EQ(result["user"], "KadiusLunarflame");
    ASSERT_EQ(result["password"], "Mellon");
    ASSERT_EQ(result["host"], "srv.lul");
    ASSERT_EQ(result["port"], "23");
}

TEST(PARSER_TESTS, TELNET_PARSING2) {

    std::string URL = "telnet://@srv.lul/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "telnet");
    ASSERT_EQ(result["user"], "");
    ASSERT_EQ(result["password"], "");
    ASSERT_EQ(result["host"], "srv.lul");
    ASSERT_EQ(result["port"], "23");
}

TEST(PARSER_TESTS, TELNET_PARSING3) {

    std::string URL = "telnet://srv.lul/";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "telnet");
    ASSERT_EQ(result["user"], "");
    ASSERT_EQ(result["password"], "");
    ASSERT_EQ(result["host"], "srv.lul");
    ASSERT_EQ(result["port"], "23");
}

TEST(PARSER_TESTS, MAILTO_PARSING1) {

    std::string URL = "mailto:lunarblessed@gmail.com";
    solar::parser parser;
    auto result = parser.parse(URL);

    ASSERT_EQ(result["protocol"], "mailto");
    ASSERT_EQ(result["mail"], "lunarblessed@gmail.com");
}



#endif //URL_TESTS_HPP
