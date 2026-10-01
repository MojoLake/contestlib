#set document(title: "Contest Library", author: "Mojolake")
#set page(
  paper: "a4",
  margin: (x: 9mm, y: 9mm),
  columns: 2,
  header: context [
    #set text(size: 7pt, fill: luma(90))
    Contest Library #h(1fr) #counter(page).display()
  ],
)
#set text(font: ("New Computer Modern", "Libertinus Serif"), size: 8pt)
#set par(justify: true, leading: 0.45em)
#set heading(numbering: "1.1", outlined: true)
#show heading.where(level: 1): it => block(above: 0.7em, below: 0.35em)[
  #set text(size: 13pt, weight: "bold")
  #it
]
#show heading.where(level: 2): it => block(above: 0.6em, below: 0.25em)[
  #set text(size: 10pt, weight: "bold")
  #it
]
#show raw.where(block: true): it => block(
  inset: 4pt,
  breakable: true,
  width: 100%,
  it,
)

#align(center)[
  #text(size: 20pt, weight: "bold")[Contest Library]
  #linebreak()
  #text(size: 9pt)[Algorithms and data structures reference]
]

#outline(title: [Contents], depth: 2)

= .vimrc

```vim
set cin aw ai is ts=4 sw=4 tm=50 nu rnu noeb bg=dark ru cul
sy on
```

= Graph

#include "content/graph/dinic.typ"
