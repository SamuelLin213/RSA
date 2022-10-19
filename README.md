# RSA
Inputs
* First line takes two integers e and n, which represents public key pair
* Second line takes in m, which is length of encoded message
* Takes in m integers, representing the encoded message

Outputs
* First line outputs p, q, phi(n) and d; p < q, p*q = n and phi(n) = (p-1)*(q-1)
* Then, output decoded message in integer
* Output the decoded messgein the English alphabet, with all letters being uppercase
* In the case that the public key isn't valid(p or q isn't prime, p == q, e isn't coprime w/ phi(n) ), an error message will output.
