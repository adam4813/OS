bits 64

segment .text
  global _ftol2_sse
  global addint

_ftol2_sse:
  movq qword [rsp - 8], xmm0
  fistp qword [rsp - 8]
  mov rbx, rcx
  ret
