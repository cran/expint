(TeX-add-style-hook
 "expint"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "x11names" "english")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("fontenc" "T1") ("inputenc" "utf8") ("natbib" "round") ("helvet" "scaled=0.92") ("mathpazo" "sc") ("Sweave" "noae" "inconsolata")))
   (add-to-list 'LaTeX-verbatim-environments-local "Verbatim")
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "href")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "fontenc"
    "inputenc"
    "amsmath"
    "natbib"
    "babel"
    "microtype"
    "helvet"
    "mathpazo"
    "Sweave"
    "framed"
    "xcolor"
    "hyperref")
   (TeX-add-symbols
    '("file" 1)
    '("samp" 1)
    '("code" 1)
    '("pkg" 1)
    "Ei"
    "FrameCommand")
   (LaTeX-add-labels
    "sec:introduction"
    "sec:expint"
    "eq:E1"
    "eq:Ei_vs_E1"
    "eq:En_vs_gammainc"
    "eq:En:recurrence"
    "eq:En:asymptotic"
    "sec:gammainc"
    "eq:gammainc"
    "eq:gammainc_vs_pgamma"
    "sec:interfaces"
    "sec:api"
    "sec:implementation"
    "sec:alternatives"
    "sec:examples")
   (LaTeX-add-environments
    '("exercice" LaTeX-env-args ["argument"] 0))
   (LaTeX-add-bibliographies)
   (LaTeX-add-xcolor-definecolors
    "link"
    "url"
    "citation"
    "codebg"))
 :latex)

