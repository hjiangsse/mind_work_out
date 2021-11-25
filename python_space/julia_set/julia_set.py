if __name__ == "__main__":
    c = -0.62772 - 0.42193j
    z1 = 0 + 0j
    for n in range(30):
        z1 = z1 * z1 + c
        print("{}: z1={:33}, abs(z1) = {:0.2f}, c={}".format(n, z1, abs(z1), c))
        
    print("-------------------------------------------------------------------")
    
    z2 = -0.82 + 0j
    for n in range(10):
        z2 = z2 * z2 + c
        print("{}: z2={:33}, abs(z2) = {:0.2f}, c={}".format(n, z2, abs(z2), c))

