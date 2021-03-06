// CppAndLuaCallTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

extern "C" {  // 表明按照类C的编译和链接规约 可以直接使用 #include "lua.hpp" 代替
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/// lua 5.1参考手册 
/// https://www.codingnow.com/2000/download/lua_manual.html#luaL_newstate

void cpp_call_lua() {
	// 初始化lua环境
	//lua_State *L = lua_open();  // lua5.1中使用luaL_newstate代替lua_open，lua_open不应该被直接调用
	lua_State *L = luaL_newstate();  
	if (L == NULL) {
		cout << "lua open failed !" << endl;
	}
	//luaopen_base(L);		// 打开lua基础库
	luaL_openlibs(L);		// 打开lua的io,string,math,table等高级库

	int ret = luaL_dofile(L, "test.lua");
	if (ret) {
		cout << "lua dofile error !" << endl;
		return;
	}

	// 获取t[k]的值，k是字符串key
	lua_getglobal(L, "str");  // 根据name获取全局变量，并压入栈顶
	cout << "str is " << lua_tostring(L, -1) << endl;  // 读取全局变量

	lua_getglobal(L, "tab1");
	lua_getfield(L, -1, "k1");  // 根据index索引处的table变量获取key的值
	cout << "tab1.k1 is " << lua_tostring(L, -1) << endl;  // 将给定索引处的值转换为指定类型

	lua_getfield(L, -2, "k2");
	cout << "tab1.k2 is " << lua_tonumber(L, -1) << endl;

	// 获取t[index]的值，index是整型索引
	lua_getglobal(L, "tab2");
	lua_pushnumber(L, 4);  // 将一个数字压入栈顶
	lua_gettable(L, -2);   // 将t[k]压入栈顶，t是index索引处的表，k是栈顶的值
	cout << "tab2.4 is " << lua_tonumber(L, -1) << endl;

	// 调用函数
	lua_getglobal(L, "print_test");
	lua_call(L, 0, 0);  // 调用一个函数，参数2表示传递给lua函数的参数个数，参数3表示返回值的个数

						// 调用有参有返回值函数
	lua_getglobal(L, "add_sub");
	lua_pushnumber(L, 2);
	lua_pushnumber(L, 3);
	lua_call(L, 2, 2);
	if (lua_isnumber(L, -1)) {
		cout << "a - b is " << lua_tonumber(L, -1) << endl;
	}
	lua_pop(L, 1);  // 从栈中弹出n个元素
	cout << "a + b is " << lua_tonumber(L, -1) << endl;

	// 释放lua环境
	lua_close(L);
}

static int cpp_add_sub(lua_State *L) {
	int b = lua_tonumber(L, -1);  // 获取第二个参数
	int a = lua_tonumber(L, -2);  // 获取第一个参数
	lua_pushnumber(L, a + b);	// 压入第一个返回值
	lua_pushnumber(L, a - b);	// 压入第二个返回值
	return 2;  // 表示返回值的个数
}

void lua_call_cpp() {
	lua_State *L = luaL_newstate();
	if (L == NULL) {
		cout << "lua open failed !" << endl;
	}
	luaL_openlibs(L);		// 打开lua的io,string,math,table等高级库
	int ret = luaL_dofile(L, "test.lua");
	if (ret) {
		cout << "lua dofile error !" << endl;
		return;
	}
	lua_register(L, "cpp_add_sub", cpp_add_sub);  // 将函数注册到lua的全局变量中

	lua_getglobal(L, "call_add_sub_from_cpp");  // 调用lua的call_add_sub_from_cpp函数，这个函数内部会调用C++函数
	lua_call(L, 0, 0);  
}

extern "C" int cpp_show_msg_box(lua_State *L) {
	cout << "print from cpp : cpp_show_msg_box" << endl;
	return 0;  // 返回值0个
}

//
// 导出函数列表
//
static luaL_Reg lua_libs[] = {
	{"cpp_show_msg_box", cpp_show_msg_box },
};

//
// dll入口函数，lua调用此dll的入口函数
// 当在lua中加载CppAndLuaCallTest.dll时，lua会根据此dll名字调用对应的函数 luaopen_dll名称
//
extern "C" __declspec(dllexport) 
int luaopen_CppAndLuaCallTest(lua_State* L) {
	luaL_register(L, "CppAndLuaCallTest", lua_libs);
	return 1;
}


int main()
{
	cpp_call_lua();

	lua_call_cpp();

	cin.get();
    return 0;
}



