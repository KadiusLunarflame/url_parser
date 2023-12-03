//
// Created by kadius on 04.12.23.
//

#ifndef URL_PARSER_HPP
#define URL_PARSER_HPP

#include <iostream>
#include <unordered_map>

namespace solar {
    class parser {
        using return_type = std::unordered_map<std::string_view ,std::string_view>;
    public:
        parser() = default;

    public:
        return_type parse(std::string_view url) {

            if(url.substr(0,5) == "<URL:" && url.back() == '>') {
                url = url.substr(5);
                url.remove_suffix(1);
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

                //<protocol>://<host>:<part>
                if (r == std::string_view::npos) {
                    //auto hostport = part;

                    auto iindex = part.find(':');
                    if (iindex == std::string_view::npos) {
                        result["host"] = part;
                        result["port"] = "80";
                        return result;
                    }

                    result["host"] = part.substr(0, iindex);
                    ++iindex;
                    result["port"] = part.substr(iindex);
                    return result;
                }

                //<protocol>://<host>:<part>/

                auto hostport = part.substr(l, r);
                auto iindex = hostport.find(':');

                if (iindex == std::string_view::npos) {
                    result["host"] = hostport;
                    result["port"] = "80";
                } else {
                    result["host"] = hostport.substr(0, iindex);
                    ++iindex;
                    result["port"] = hostport.substr(iindex);
                }
                if (++r == part.length()) {
                    return result;
                }

                l = r;
                part = part.substr(l);

                l = 0;
                r = part.find('?');

                //<protocol>://<host>:<part>/<path>
                if (r == std::string_view::npos) {
                    result["path"] = part;
                    return result;
                }

//              <protocol>://<host>:<part>/<path>?<searchpart>
                result["path"] = part.substr(0, r);
                ++r;
                result["searchpart"] = part.substr(r);
                if (result["searchpart"].back() == '/')
                    result["searchpart"].remove_suffix(1);

                return result;
            }
            else if (protocol == "ftp") {
                result["protocol"] = "ftp";

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
                r = part.find('@');

                if (r == std::string_view::npos) {
                    r = part.find('/');

                    //no <path>
                    if(r == std::string_view::npos) {

                        auto iindex = part.find(':');

                        if(iindex == std::string_view::npos) {
                            result["host"] = part;
                            result["port"] = "21";
                            if(result["host"].back() == '/')
                                result["host"].remove_suffix(1);

                            return result;
                        }

                        result["host"] = part.substr(0,iindex);
                        result["port"] = part.substr(iindex+1);

                        if(result["port"].back() == '/')
                            result["port"].remove_suffix(1);

                        return result;
                    }
                    //with <path>
                    auto hostport = part.substr(0,r);
                    auto iindex = hostport.find(':');

                    if(iindex == std::string_view::npos) {
                        result["host"] = hostport;
                        result["port"] = "21";
                        if(result["host"].back() == '/')
                            result["host"] = hostport.substr(0,hostport.length()-1);

                        result["path"] = part.substr(r+1);

                        return result;
                    }

                    result["host"] = hostport.substr(0,iindex);
                    result["port"] = hostport.substr(iindex+1);
                    result["path"] = part.substr(r+1);

                    if(result["port"].back() == '/')
                        result["port"] = hostport.substr(iindex+1, hostport.length()-1);

                    return result;

                } else {
                    auto userpasswd = part.substr(0,r);

                    auto iindex = userpasswd.find(':');

                    if(userpasswd.empty()) {
                        result["user"] = "";
                        result["password"] = "";
                    } else {
                        if (iindex == userpasswd.length() - 1) {
                            result["user"] = userpasswd.substr(0, iindex);
                            result["password"] = "EMPTY";
                        } else if (iindex == std::string_view::npos) {
                            result["user"] = userpasswd;
                        } else {
                            result["user"] = userpasswd.substr(0, iindex);
                            result["password"] = userpasswd.substr(iindex + 1);
                        }
                    }
                    part = part.substr(r+1);

                    r = part.find('/');

                    if(r == std::string_view::npos) {

                        r = part.find(':');

                        if(r == std::string_view::npos) {
                            result["host"] = part;
                            result["port"] = "21";
                            if(result["host"].back() == '/')
                                result["host"].remove_suffix(1);

                            return result;
                        }
                        result["host"] = part.substr(0,r);
                        result["port"] = part.substr(r+1);

                        if(result["port"].back() == '/')
                            result["port"].remove_suffix(1);
                    }

                    auto hostport = part.substr(0,r);
                    iindex = hostport.find(':');

                    if(iindex == std::string_view::npos) {
                        result["host"] = hostport;
                        result["port"] = "21";
                        if(result["host"].back() == '/')
                            result["host"].remove_suffix(1);
                        result["path"] = part.substr(r+1);

                        return result;
                    }
                    result["host"] = hostport.substr(0,iindex);
                    result["port"] = hostport.substr(iindex+1);
                    if(result["port"].back() == '/')
                        result["port"].remove_suffix(1);

                    result["path"] = part.substr(r+1);

                    return result;
                }

            }
            else if (protocol == "gopher") {
                result["protocol"] = "gopher";

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

                //<protocol>://<host>:<part>
                if (r == std::string_view::npos) {
                    //auto hostport = part;

                    auto iindex = part.find(':');
                    if (iindex == std::string_view::npos) {
                        result["host"] = part;
                        result["port"] = "70";
                        return result;
                    }

                    result["host"] = part.substr(0, iindex);
                    ++iindex;
                    result["port"] = part.substr(iindex);
                    return result;
                }

                //<protocol>://<host>:<part>/

                auto hostport = part.substr(l, r);
                auto iindex = hostport.find(':');

                if (iindex == std::string_view::npos) {
                    result["host"] = hostport;
                    result["port"] = "70";
                } else {
                    result["host"] = hostport.substr(0, iindex);
                    ++iindex;
                    result["port"] = hostport.substr(iindex);
                }
                if (++r == part.length()) {
                    return result;
                }

                l = r;
                result["path"] = part.substr(l);
                return result;
                //TODO: parse path
            }
            else if (protocol == "nntp") {
                result["protocol"] = "nntp";

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

                //<protocol>://<host>:<part>
                if (r == std::string_view::npos) {
                    //auto hostport = part;

                    auto iindex = part.find(':');
                    if (iindex == std::string_view::npos) {
                        result["host"] = part;
                        result["port"] = "119";
                        return result;
                    }

                    result["host"] = part.substr(0, iindex);
                    ++iindex;
                    result["port"] = part.substr(iindex);
                    return result;
                }

                //<protocol>://<host>:<part>/

                auto hostport = part.substr(l, r);
                auto iindex = hostport.find(':');

                if (iindex == std::string_view::npos) {
                    result["host"] = hostport;
                    result["port"] = "119";
                } else {
                    result["host"] = hostport.substr(0, iindex);
                    ++iindex;
                    result["port"] = hostport.substr(iindex);
                }
                if (++r == part.length()) {
                    return result;
                }

                l = r;
                part = part.substr(l);

                r = part.find('/');

                if (r == std::string_view::npos || r == part.length() - 1) {
                    result["newsgroup"] = part.substr(0, r);
                    return result;
                }

                result["newsgroup"] = part.substr(0, r);
                result["article"] = part.substr(r + 1);
                return result;
            }
            else if(protocol == "wais") {
                result["protocol"] = "wais";

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

                //<protocol>://<host>:<part>
                if (r == std::string_view::npos) {
                    //auto hostport = part;

                    auto iindex = part.find(':');
                    if (iindex == std::string_view::npos) {
                        result["host"] = part;
                        result["port"] = "210";
                        return result;
                    }

                    result["host"] = part.substr(0, iindex);
                    ++iindex;
                    result["port"] = part.substr(iindex);
                    return result;
                }

                //<protocol>://<host>:<part>/

                auto hostport = part.substr(l, r);
                auto iindex = hostport.find(':');

                if (iindex == std::string_view::npos) {
                    result["host"] = hostport;
                    result["port"] = "210";
                } else {
                    result["host"] = hostport.substr(0, iindex);
                    ++iindex;
                    result["port"] = hostport.substr(iindex);
                }
                if (++r == part.length()) {
                    return result;
                }

                l = r;
                part = part.substr(l);

                r = part.find('?');
                if (r == std::string::npos) {
                    r = part.find('/');

                    if (r == std::string::npos) {
                        result["database"] = part;
                        return result;
                    }

                    result["database"] = part.substr(0, r);
                    part = part.substr(r+1);
                    r = part.find('/');

                    result["wtype"] = part.substr(0,r);
                    result["wpath"] = part.substr(r+1);
                    return result;
                }

                result["database"] = part.substr(0,r);
                result["searchpart"] = part.substr(r+1);
                return result;
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

                //<protocol>://<host>:<part>
                if (r == std::string_view::npos) {
                    //auto hostport = part;

                    auto iindex = part.find(':');
                    if (iindex == std::string_view::npos) {
                        result["host"] = part;
                        result["port"] = "1525";
                        return result;
                    }

                    result["host"] = part.substr(0, iindex);
                    ++iindex;
                    result["port"] = part.substr(iindex);
                    return result;
                }

                //<protocol>://<host>:<part>/

                auto hostport = part.substr(l, r);
                auto iindex = hostport.find(':');

                if (iindex == std::string_view::npos) {
                    result["host"] = hostport;
                    result["port"] = "1525";
                } else {
                    result["host"] = hostport.substr(0, iindex);
                    ++iindex;
                    result["port"] = hostport.substr(iindex);
                }
                if (++r == part.length()) {
                    return result;
                }

                l = r;
                part = part.substr(l);

                r = part.find(';');

                if(r == std::string_view::npos) {
                    result["hsoname"] = part;
                    return result;
                }
                result["hsoname"] = part.substr(0,r);
                result["parameters"] = part.substr(r+1);
                return result;
            }
            else if (protocol == "telnet") {
                result["protocol"] = "telnet";

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
                r = part.find('@');

                if (r == std::string_view::npos) {
                    r = part.find('/');

                    //no <path>
                    if(r == std::string_view::npos) {

                        auto iindex = part.find(':');

                        if(iindex == std::string_view::npos) {
                            result["host"] = part;
                            result["port"] = "21";
                            if(result["host"].back() == '/')
                                result["host"].remove_suffix(1);

                            return result;
                        }

                        result["host"] = part.substr(0,iindex);
                        result["port"] = part.substr(iindex+1);

                        if(result["port"].back() == '/')
                            result["port"].remove_suffix(1);
                        return result;
                    }
                    //with <path>
                    auto hostport = part.substr(0,r);
                    auto iindex = hostport.find(':');

                    if(iindex == std::string_view::npos) {
                        result["host"] = hostport;
                        result["port"] = "23";
                        if(result["host"].back() == '/')
                            result["host"].remove_suffix(1);

                        result["path"] = part.substr(r+1);

                        return result;
                    }

                    result["host"] = hostport.substr(0,iindex);
                    result["port"] = hostport.substr(iindex+1);
                    result["path"] = part.substr(r+1);

                    if(result["port"].back() == '/')
                        result["port"].remove_suffix(1);

                    return result;

                } else {
                    auto userpasswd = part.substr(0,r);

                    auto iindex = userpasswd.find(':');

                    if(userpasswd.empty()) {
                        result["user"] = "";
                        result["password"] = "";
                    } else {
                        if (iindex == userpasswd.length() - 1) {
                            result["user"] = userpasswd.substr(0, iindex);
                            result["password"] = "EMPTY";
                        } else if (iindex == std::string_view::npos) {
                            result["user"] = userpasswd;
                        } else {
                            result["user"] = userpasswd.substr(0, iindex);
                            result["password"] = userpasswd.substr(iindex + 1);
                        }
                    }
                    part = part.substr(r+1);

                    r = part.find('/');

                    if(r == std::string_view::npos) {

                        r = part.find(':');

                        if(r == std::string_view::npos) {
                            result["host"] = part;
                            result["port"] = "23";
                            if(result["host"].back() == '/')
                                result["host"].remove_suffix(1);

                            return result;
                        }
                        result["host"] = part.substr(0,r);
                        result["port"] = part.substr(r+1);

                        if(result["port"].back() == '/')
                            result["port"].remove_suffix(1);
                    }

                    auto hostport = part.substr(0,r);
                    iindex = hostport.find(':');

                    if(iindex == std::string_view::npos) {
                        result["host"] = hostport;
                        result["port"] = "23";
                        if(result["host"].back() == '/')
                            result["host"].remove_suffix(1);
                        result["path"] = part.substr(r+1);

                        return result;
                    }
                    result["host"] = hostport.substr(0,iindex);
                    result["port"] = hostport.substr(iindex+1);
                    if(result["port"].back() == '/')
                        result["port"].remove_suffix(1);

                    result["path"] = part.substr(r+1);

                    return result;
                }
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


#endif //URL_PARSER_HPP
