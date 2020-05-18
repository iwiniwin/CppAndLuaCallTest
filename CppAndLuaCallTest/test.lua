str = "name"

tab1 = {
    k1 = "v1",
    k2 = 2,
}

tab2 = {
    [4] = 4,
    kk = 3,
}

function print_test(  )
    print("lua print : test")
end

function add_sub( a, b )
    print("lua print : a = " .. a)
    print("lua print : b = " .. b)
    print("lua print : a + b = " .. a + b)
    print("lua print : a - b = " .. a - b)
    return a + b, a - b
end

function call_add_sub_from_cpp(  )
    local sum, diff = cpp_add_sub(10, 6);
    print("lua print : 10 + 6 = " .. sum)
    print("lua print : 10 - 6 = " .. diff)
end


-- 调用CppAndLuaCallTest.dll导出的cpp_show_msg_box方法
-- CppAndLuaCallTest.dll需要修改项目配置类型为动态库(.dll)生成
-- 
function call_func_form_cpp_dll( ... )
    local t = require("CppAndLuaCallTest")
    t.cpp_show_msg_box()
end
-- CppAndLuaCallTest.dll生成后，打开下方函数注释，lua文件被加载时将调用c++方法
-- call_func_form_cpp_dll()
