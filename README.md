# Introduction
Today, there are many matlab toolboxes not maintaining.
Therefore, if users utilize them, they should use supported old version.
However, in case of using several toolboxes, it is possible that we face not to be able to solve by this.
This repository provides a converter from old matlab version to newer.

# Requirements
Windows10<br>
Linux & mac (if possible)

# Installing
+ TODO : write

# support MATLAB versions
+ R2013a(not implement)
+ R2019a(not implement)


# idea
+ tokenizer -> now coding<br>
  build token list for old version.<br>
+ parser (not yet)<br>
  build Concrete Syntax Tree(CST) for old version.<br>
+ converter (not yet)<br>
  analyze as new version & fix error.<br>
  (need to implement every version)<br>
+ unparser (not yet)<br>
  reconstruct token list from CST.<br>
+ untokenizer (not yet)<br>
  reconstruct source code.<br>

# features (future)
+ customize converter without recompiling.
  I think all source code and versions cannnot be supported only by myself. Therefore, we need to correspond unsupported code or version by yourself. In addition, this procedure have to be easy for non C-language user (in particular, for matlab user). Therefore, I plan to implement function that achieve it by only coding matlab script.
