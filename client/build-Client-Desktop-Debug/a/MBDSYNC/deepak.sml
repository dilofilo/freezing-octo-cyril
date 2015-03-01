                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              fun sub3 (x, y, zs) = map (fn z => if z = x then y else z) zs
fun subs(a,b,c,i)=
 if i>=0 then
   if List.nth(a,0)>=List.nth(b,0) then	
        (if (List.nth(a,i)>=List.nth(b,i)) andalso (i>=0) then
            subs(a,b,(List.nth(a,i)-List.nth(b,i))::c,i-1)
	else if List.nth(a,i)<List.nth(b,i) andalso (i>=0) then
  	    subs(sub3 (List.nth(a,i-1),List.nth(a,i-1)-1,a),b,((List.nth(a,i)+10)-List.nth(b,i))::c,i-1)
	else 
            c
       )
  else
	[0]
 else 
   c
 
fun equ(a,b,q)=
    
let
val x =length a
val y =length b-q
val t=0
in
 if length a >= length b then
      if q< (x-y) andalso (x>y) then
	 equ(a,t::b,q+1)
      else
         b
 else 
       [0]
     
end;
fun p(a,b)=subs(a,equ(a,b,0),[],(length a)-1);
 

 
     
                                                      


