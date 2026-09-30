#let algorithm(title, path, complexity: none, notes: none) = [
  == #title
  #if complexity != none [
    *Complexity:* #complexity
  ]
  #if notes != none [
    #notes
  ]
  #raw(read(path), lang: "cpp", block: true)
]
