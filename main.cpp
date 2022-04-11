#include <iostream>
#include <regex>
#include <vector>
#include <string.h>

using namespace std;

void test01()
{
    string UnicomNumber("\\b(1)(3[0-2]|[4578]5|[5-9]6)(\\d{4})(\\d{4})\\b");
    regex r(UnicomNumber);
    string fmt = "$1$2 $3 $4";
    string number = "14512345678";
    auto result = regex_replace(number,r,fmt);
    // 格式化输出电话号码
    cout << result << endl;
}


void test02()
{
    //匹配联通号码
    string UnicomNumber("\\b(1)(3[0-2]|[4578]5|[5-9]6)(\\d{4})(\\d{4})\\b");
    regex r(UnicomNumber);
    string testNumbers("130123456789 23112345678 7602125 1320000 16512345678 14512345678 17612345678");
    for (sregex_iterator it(testNumbers.begin(), testNumbers.end(), r), end_it;it != end_it;++it) {
        cout << it->str() << endl;
    }
}

void test_regex_replace()
{
    string pattern{ "\\d{18}|\\d{17}X" }; // id card
    regex re(pattern);

    vector<string> str{ "123456789012345678", "abcd123456789012345678efgh",
                        "abcdefbg", "12345678901234567X" };
    string fmt{ "********" };

    /* std::regex_replace:
        在整个字符序列中查找正则表达式re的所有匹配
        算法每次成功匹配后，就根据参数fmt对匹配字符串进行替换
    */

    for (auto tmp : str) {
        string ret = regex_replace(tmp, re, fmt);
        fprintf(stderr, "src: %s, dst: %s\n", tmp.c_str(), ret.c_str());
    }
}

void test_match_suffix(){
    string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    regex txt_regex("[a-z]+\\.txt");
    for (const auto &fname: fnames)
    {
        cout << fname << ": " << regex_match(fname, txt_regex) << endl;
    }
}

void test_regex_replace2()
{
    // reference: http://www.cplusplus.com/reference/regex/regex_replace/
    string s("there is a subsequence in the string\n");
    regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    // using string/c-string (3) version:
    cout << regex_replace(s, e, "sub-$2");

    // using range/c-string (6) version:
    string result;
    regex_replace(back_inserter(result), s.begin(), s.end(), e, "$2");
    cout << result;

    // with flags:
    cout << regex_replace(s, e, "$1 and $2", std::regex_constants::format_no_copy) << endl;
}


int main(int argc, char *argv[])
{

    // 20191224 16:04:05.125049 2970 ERROR 5266030 chello, world - LogTest.cpp:thr_1():20
    string log = "aaa - 20191224 16:04:05.125049 2970 ERROR 5266030 chello, world1 - LogTest.cpp:thr_1():20\
            bbb - 20201224 18:04:05.125049 2970 ERROR 5266031 chello, world2 - LogTest.cpp:thr_2():20\
      ccc - 20211224 20:04:10.125049 2970 ERROR 5266032 chello, world3 - LogTest.cpp:thr_3():20";
      // gettime
      string timepattern("\\d{8} \\d{2}:\\d{2}:\\d{2}.\\d{6}");
    regex reg(timepattern);
    smatch results;
    // regex_search can only get the first matching str
    if (regex_search(log,results,reg)){
        cout << results.str() << endl;
    }

    cout << "----------------------------" << endl;

    // iter is used to find all matched strs,end_it is an empty iterator
    for(sregex_iterator iter(log.begin(),log.end(),reg),end_it; iter != end_it; ++iter){
        cout << iter->str() << endl;
    }

    cout << "----------------------------" << endl;
    for(sregex_iterator iter(log.begin(),log.end(),reg),end_it; iter != end_it; ++iter){
        cout << iter->str() << endl;
        auto pos = iter->prefix().length();

        // prefix和suffix函数可以得到匹配之前和之后的ssub_match对象。
        cout << "prestr (" << iter->prefix().str().substr(pos - 6,6) << ")"
             << "[" << iter->str() << "]"
             << iter->suffix().str().substr(0,59) << endl;
    }


    //test01();
    //test02();

    //test_regex_replace();
    //test_regex_replace2();

    test_match_suffix();



    return 0;
}
