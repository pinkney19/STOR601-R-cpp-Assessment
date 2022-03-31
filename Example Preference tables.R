#Examples to show it works

#4x4 Example
p1_init = data.frame(A = c("c","b","d","a"),
                    B = c("b","a","c","d"),
                    C = c("b","d","a","c"),
                    D = c("c","a","d","b"), stringsAsFactors = F)

p2_init = data.frame(a = c("A","B","D","C"),
                     b = c("C","A","D","B"),
                     c = c("C","B","D","A"),
                     d = c("B","A","C","D"), stringsAsFactors = F)

#use package to find stable matching
fundamental_algorithm(p1_init,p2_init)

#5x5 Example
p1_5 = data.frame(A=c("a","b","c","d","e"), 
                  B=c("b","c","d","e","a"),
                  C=c("c","d","e","a","b"),
                  D=c("d","e","a","b","c"),
                  E=c("e","a","b","c","d"), stringsAsFactors = F)

p2_5 = data.frame(a=c("B","C","D","E","A"),
                  b=c("C","D","E","A","B"),
                  c=c("D","E","A","B","C"),
                  d=c("E","A","B","C","D"),
                  e=c("A","B","C","D","E"), stringsAsFactors = F)

#use package to find stable matching
fundamental_algorithm(p1_5,p2_5)
