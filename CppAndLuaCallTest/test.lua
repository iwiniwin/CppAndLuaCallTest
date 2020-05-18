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
