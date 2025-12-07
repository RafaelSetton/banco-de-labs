C = 0.3

yb, xc, ta, tb, tc, t = [int(x) for x in input().split()]

da = (t-ta)*C
db = (t-tb)*C
dc = (t-tc)*C

x = (da*da+xc*xc-dc*dc)//(2*xc)
y = (da*da+yb*yb-db*db)//(2*yb)

print(x, y)


