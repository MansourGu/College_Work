#include"stdafx.h"
#include <string>
#include"cppjieba/include/cppjieba/Jieba.hpp"
#include<vector>
#include<iostream>//for cout
#include<Windows.h>
#include<wchar.h>
#include <string>
#include<stdio.h>
#include<map>	
#include<algorithm>
#include <io.h>//for _finddata_t¡¢ _findnext
#include<set>
#pragma once
using namespace std;

const char* const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";
	cppjieba::Jieba jieba(DICT_PATH,
	HMM_PATH,
	USER_DICT_PATH,
	IDF_PATH,
	STOP_WORD_PATH);
vector<string> words;
vector<cppjieba::Word> jiebawords;
map<string, vector<string> > indextable;