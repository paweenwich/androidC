dofile("script/AScript_org_puremvc_lua_multicore_help_oop.lua");

A = class("A");
AA = class("AA",A);
function A:ctor()
    print("ctor");
end;

function A:func1()
    print("func1");
end;

B = class("B");
function B:ctor()
    self.a = A.new();
    A.text = "text set by B";
end;
function B:func1()
    a.func1();
end;

a = A.new();
print("A.text="..tostring(A.text));
print("a.text="..tostring(a.text));
b = B.new();
print("A.text="..tostring(A.text));
print("a.text="..tostring(a.text));
print("b.text="..tostring(b.text));
aa = AA.new();
print("a.func1="..tostring(a.func1));
print("b.func1="..tostring(b.func1));
print("aa.func1="..tostring(aa.func1));
print("aa.text="..tostring(aa.text));
a:func1();
b.func1();
-- rerefine func1
function A:func1()
    print("func1.1");
end;
a:func1();
b.func1();
print("a.func1="..tostring(a.func1));
print("b.func1="..tostring(b.func1));
print("aa.func1="..tostring(aa.func1));
function a:func1()
    print("func1 set by a:func1");
end;
a:func1();
b.func1();
print("a.func1="..tostring(a.func1));
print("b.func1="..tostring(b.func1));
print("aa.func1="..tostring(aa.func1));
a.func1 = function(self)
    print("a func2");
end;
print("a.func1="..tostring(a.func1));
print("b.func1="..tostring(b.func1));
print("aa.func1="..tostring(aa.func1));
a:func1();
b.func1();
print(a.__cname);
print("Done");
