fun sub3 (x, y, zs) = map (fn z => if z = x then y else z) zs
fun subs(a,b,c,i)=
if i>=0 then
if list.nth(a,0)>=list.nth(b,0) then
                                   if list.nth(a,i)>=list.nth(b,i) then (a,b,(list.nth(a,i)-list.nth(b,i)::c),i-1)
                                    else if list.nth(a,i)<=list.nth(b,i) then (a,b,
