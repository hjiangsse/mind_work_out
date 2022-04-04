doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y
doubleSmallerNumber x = if x > 100 then x else doubleMe x
boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]
