//
// Created by kadius on 04.12.23.
//

#ifndef URL_PARSER_REGEX_PARSER_RX_HPP
#define URL_PARSER_REGEX_PARSER_RX_HPP

#include <iostream>
#include <unordered_map>
#include <regex>

namespace solar {
    class parser_rx {
        using return_type = std::unordered_map<std::string ,std::string>;
    public:
        parser_rx() = default;

    public:
        return_type parse(std::string url) {

            if (url.substr(0, 5) == "<URL:" && url.back() == '>') {
                url = url.substr(5);
                url.pop_back();
            }

            return_type result;
            std::string protocol;

            if (url.empty()) {
                std::cout << "[DONE]: EMPTY URL" << std::endl;
                return result;
            }

            size_t length = url.length();
            size_t l{};
            size_t r{};
            r = url.find(':');

            if (r == std::string_view::npos) {
                std::cout << "[FAILED]: MALFORMED URL" << std::endl;
                return result;
            }

            protocol = url.substr(l, r);

            //tolower
            for (auto &it: protocol)
                if ('A' <= it && it <= 'Z')
                    it = it + 0x20;


            if (protocol == "https") {
                result["protocol"] = "https";

                std::regex rx1{"https://.*\/.*?.*"};
                if(std::regex_match(url, rx1)) {
                    url = url.substr(8);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);

                    url = url.substr(r+1);
                    r = url.find('?');
                    result["path"] = url.substr(0,r);
                    result["searchpart"] = url.substr(r+1);
                    result["port"] = "80";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx2{"https://.*\/.*"};
                if(std::regex_match(url, rx2)) {
                    url = url.substr(8);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);

                    url = url.substr(r+1);
                    result["path"] = url.substr(r);
                    result["port"] = "80";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx3{"https://.*\/"};
                if(std::regex_match(url, rx3)) {
                    url = url.substr(8);
                    url.pop_back();
                    result["host"] = url;
                    result["port"] = "80";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx4{"https://.*"};
                if(std::regex_match(url, rx4)) {
                    url = url.substr(8);
                    std::cout << "HERE " << url << std::endl;
                    result["host"] = url;
                    result["port"] = "80";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

            }
            else if (protocol == "ftp") {
                result["protocol"] = "ftp";

                std::regex rx2{"ftp://.*:@.*\/.*"};
                if(std::regex_match(url, rx2)) {
                    url = url.substr(6);

                    r = url.find(':');
                    result["user"] = url.substr(0,r);\
                    result["password"] = "EMPTY";

                    ++r;
                    ++r;
                    url = url.substr(r);

                    r = url.find('/');
                    result["host"] = url.substr(0,r);
                    result["port"] = "21";

                    result["path"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx21{"ftp://.*:.*@.*\/.*"};
                if(std::regex_match(url, rx21)) {
                    url = url.substr(6);

                    r = url.find(':');
                    result["user"] = url.substr(0,r);
                    ++r;
                    url.substr(r);
                    r = url.find('@');
                    result["password"] = url.substr(0,r);
                    ++r;
                    url = url.substr(r);

                    r = url.find('/');
                    result["host"] = url.substr(0,r);
                    result["port"] = "21";

                    result["path"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx22{"ftp://.*:@.*"};
                if(std::regex_match(url, rx22)) {
                    url = url.substr(6);

                    r = url.find(':');
                    result["user"] = url.substr(0,r);\
                    result["password"] = "EMPTY";

                    ++r;
                    ++r;
                    url = url.substr(r);

                    result["host"] = url;
                    result["port"] = "21";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx3{"ftp://@.*\/.*"};
                if(std::regex_match(url, rx3)) {
                    url = url.substr(7);

                    result["user"] = "";
                    result["password"] = "";

                    r = url.find('/');
                    result["host"] = url.substr(0,r);
                    result["port"] = "21";

                    result["path"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx1{"ftp://.*/.*"};
                if(std::regex_match(url, rx1)) {
                    url = url.substr(6);

                    r = url.find('/');

                    result["host"] = url.substr(0,r);
                    result["port"] = "21";
                    result["path"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx9{"ftp://.*/"};
                if(std::regex_match(url, rx9)) {
                    url = url.substr(6);

                    r = url.find('/');

                    result["host"] = url.substr(0,r);
                    result["port"] = "21";
//                    result["path"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx10{"ftp://.*"};
                if(std::regex_match(url, rx10)) {
                    url = url.substr(6);

                    r = url.find('/');

                    result["host"] = url.substr(0,r);
                    result["port"] = "21";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }



            }
            else if (protocol == "gopher") {
                result["protocol"] = "gopher";

                std::regex rx2{"gopher://.*\/.*"};
                if(std::regex_match(url, rx2)) {
                    url = url.substr(9);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);
                    result["path"] = url.substr(r+1);

                    result["port"] = "70";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx3{"gopher://.*\/"};
                if(std::regex_match(url, rx3)) {
                    url = url.substr(9);
                    url.pop_back();
                    result["host"] = url;
                    result["port"] = "70";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx4{"gopher://.*"};
                if(std::regex_match(url, rx4)) {
                    url = url.substr(9);
                    result["host"] = url;
                    result["port"] = "70";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }
            }
            else if (protocol == "nntp") {
                result["protocol"] = "nntp";

                std::regex rx1{"nntp://.*\/.*\/.*"};
                if(std::regex_match(url, rx1)) {
                    url = url.substr(7);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);

                    url = url.substr(r+1);
                    r = url.find('/');
                    result["newsgroup"] = url.substr(0,r);
                    result["article"] = url.substr(r+1);
                    result["port"] = "119";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx2{"nntp://.*\/.*"};
                if(std::regex_match(url, rx2)) {
                    url = url.substr(9);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);

                    url = url.substr(r+1);
                    result["newsgroup"] = url.substr(r);
                    result["port"] = "119";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx3{"nntp://.*\/"};
                if(std::regex_match(url, rx3)) {
                    url = url.substr(7);
                    url.pop_back();
                    result["host"] = url;
                    result["port"] = "119";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx4{"nntp://.*"};
                if(std::regex_match(url, rx4)) {
                    url = url.substr(7);
                    std::cout << "HERE " << url << std::endl;
                    result["host"] = url;
                    result["port"] = "119";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

            }
            else if(protocol == "wais") {
                result["protocol"] = "wais";

                std::regex rx1{"wais://.*\/.*?.*"};
                if(std::regex_match(url, rx1)) {
                    url = url.substr(7);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);
                    result["port"] = "210";
                    url = url.substr(r+1);
                    r = url.find('?');
                    result["database"] = url.substr(0,r);
                    result["searchpart"] = url.substr(r+1);
                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx2{"wais://.*\/.*\/.*\/.*"};
                if(std::regex_match(url, rx2)) {
                    url = url.substr(7);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);
                    result["port"] = "210";
                    url = url.substr(r+1);
                    r = url.find('/');
                    result["database"] = url.substr(0,r);
                    url = url.substr(r+1);
                    std::cout << url << "<- our url" << std::endl;

                    r = url.find('/');
                    result["wtype"] = url.substr(0,r);
                    result["wpath"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;

                }

                std::regex rx3{"wais://.*\/.*"};
                if(std::regex_match(url, rx3)) {
                    url = url.substr(7);

                    r = url.find('/');

                    result["host"] = url.substr(0,r);
                    result["port"] = "210";
                    result["database"] = url.substr(r+1);

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }
            }
            else if (protocol == "file") {
                result["protocol"] = "file";

                //сдвинуть курсор на 3 вправо
                l = r + 3;
                if (l >= length) {
                    std::cout << "[FAILED]: MALFORMED URL" << std::endl;
                    return result;
                }

                auto part = url.substr(l);
                if (part.empty()) {
                    std::cout << "[FAILED]: MALFORMED URL" << std::endl;
                    return result;
                }

                l = 0;
                r = part.find('/');

                result["host"] = part.substr(0,r);
                result["path"] = part.substr(r+1);
                return result;
            }
            else if (protocol == "prospero") {
                result["protocol"] = "prospero";

//                std::regex rx0{"prospero://.*\/\/.*;.*"};
//                if(std::regex_match(url, rx0)) {
//                    url = url.substr(11);
//                    r = url.find('/');
//                    result["host"] = url.substr(0,r);
//
//                    url = url.substr(r+1);
//                    r = url.find(';');
//                    result["hsoname"] = url.substr(0,r);
//                    result["parameters"] = url.substr(r+1);
//                    result["port"] = "1525";
//
//                    std::regex rxport{".*:[1-9]*"};
//                    if(std::regex_match(result["host"], rxport)) {
//                        auto str = result["host"];
//                        r = str.find(':');
//                        result["host"] = str.substr(0,r);
//                        result["port"] = str.substr(r+1);
//                    }
//
//                    return result;
//                }


                std::regex rx1{"prospero://.*\/.*;.*"};
                if(std::regex_match(url, rx1)) {
                    url = url.substr(11);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);

                    url = url.substr(r+1);
                    r = url.find(';');
                    result["hsoname"] = url.substr(0,r);
                    result["parameters"] = url.substr(r+1);
                    result["port"] = "1525";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx2{"prospero://.*\/.*"};
                if(std::regex_match(url, rx2)) {
                    url = url.substr(11);
                    r = url.find('/');
                    result["host"] = url.substr(0,r);

                    url = url.substr(r+1);
                    result["path"] = url.substr(r);
                    result["port"] = "1525";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx3{"prospero://.*\/"};
                if(std::regex_match(url, rx3)) {
                    url = url.substr(11);
                    url.pop_back();
                    result["host"] = url;
                    result["port"] = "1525";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

                std::regex rx4{"https://.*"};
                if(std::regex_match(url, rx4)) {
                    url = url.substr(8);
                    std::cout << "HERE " << url << std::endl;
                    result["host"] = url;
                    result["port"] = "1525";

                    std::regex rxport{".*:[1-9]*"};
                    if(std::regex_match(result["host"], rxport)) {
                        auto str = result["host"];
                        r = str.find(':');
                        result["host"] = str.substr(0,r);
                        result["port"] = str.substr(r+1);
                    }

                    return result;
                }

            }
            else if (protocol == "telnet") {
                result["protocol"] = "telnet";

            }
            else if (protocol == "mailto") {
                result["protocol"] = "mailto";

                l = r + 1;
                if (l >= length) {
                    std::cout << "[FAILED]: MALFORMED URL" << std::endl;
                    return result;
                }

                result["mail"] = url.substr(l);
                return result;
            }
            else if(protocol == "news") {
                result["protocol"] = "news";

                l = r + 1;
                if (l >= length) {
                    std::cout << "[FAILED]: MALFORMED URL" << std::endl;
                    return result;
                }

                auto part = url.substr(l);

                auto index = part.find('@');
                if(index == std::string_view::npos)
                    result["newsgroup"] = part;
                else
                    result["messageid"] = part;

                return result;
            }
        }

    };

}//namespace parser



#endif //URL_PARSER_REGEX_PARSER_RX_HPP
