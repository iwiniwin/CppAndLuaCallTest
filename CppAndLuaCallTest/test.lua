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



function call_func_form_cpp_dll( ... )
    package.path = package.path .. ";..\\?.dll;"
    require("Debug\\CppAndLuaCallTest")
end

call_func_form_cpp_dll()