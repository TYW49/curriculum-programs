DATAS SEGMENT
    ;此处输入数据段代码
    count db 30
    

    ;小车初始位置
    car1X db 0      ;1
    car1Y db 35

    car2X db 10     ;2
    car2Y db 78

    car3X db 24     ;3
    car3Y db 41

    car4X db 13     ;4
    car4Y db 2

    car5X db 24     ;5
    car5Y db 43
    
    car6x db 0      ;6
    car6y db 37

    gray db 78h  ;定义红绿黄灯的标志 红灯 74h  黄灯 7eh  绿灯 72h  灰色 78h
    red db 74h
    yellow db 7eh
    green db 72h

    mode db 1   ;红绿灯的模式标志
    mark db 1   ;红绿灯的总模式标志

DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS

light1 macro  l1,l2,l3  ;显示1号路口红绿灯   l1,l2,l3表示灯的颜色
    pusha

    mov ah,2   ;1
    mov bh,0
    mov dh,6
    mov dl,44
    int 10h


    mov ah,9
    mov bh,0
    mov bl,l1
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2   ;2
    mov bh,0
    mov dh,7
    mov dl,44
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l2
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2    ;3
    mov bh,0
    mov dh,8
    mov dl,44
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l3
    mov al,'o'
    mov cx,1
    int 10h

    popa

endm

light2 macro  l1,l2,l3  ;显示2号路口红绿灯   l1,l2,l3表示灯的颜色
    pusha

    mov ah,2   ;1
    mov bh,0
    mov dh,15
    mov dl,46
    int 10h


    mov ah,9
    mov bh,0
    mov bl,l1
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2   ;2
    mov bh,0
    mov dh,15
    mov dl,47
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l2
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2    ;3
    mov bh,0
    mov dh,15
    mov dl,48
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l3
    mov al,'o'
    mov cx,1
    int 10h

    popa

endm

light3  macro  l1,l2,l3  ;显示3号路口红绿灯   l1,l2,l3表示灯的颜色
    pusha
    mov ah,2   ;1
    mov bh,0
    mov dh,16
    mov dl,33
    int 10h


    mov ah,9
    mov bh,0
    mov bl,l1
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2   ;2
    mov bh,0
    mov dh,17
    mov dl,33
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l2
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2    ;3
    mov bh,0
    mov dh,18
    mov dl,33
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l3
    mov al,'o'
    mov cx,1
    int 10h

    popa

endm

light4 macro  l1,l2,l3  ;显示4号路口红绿灯   l1,l2,l3表示灯的颜色
    pusha

    mov ah,2   ;1
    mov bh,0
    mov dh,9
    mov dl,30
    int 10h


    mov ah,9
    mov bh,0
    mov bl,l1
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2   ;2
    mov bh,0
    mov dh,9
    mov dl,31
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l2
    mov al,'o'
    mov cx,1
    int 10h

    mov ah,2    ;3
    mov bh,0
    mov dh,9
    mov dl,32
    int 10h

    mov ah,9
    mov bh,0
    mov bl,l3
    mov al,'o'
    mov cx,1
    int 10h

    popa

endm

DELAY MACRO TIME ;延时宏
    LOCAL P1,P2
    PUSHA
    MOV DX,TIME
P1: MOV CX,0FF00H
P2: LOOP P2
    DEC DX
    JNZ P1
    POPA
    ENDM


Pain macro x,y,as,z,sx  ;显示字符，x,y分别为行号、列号，as 字符ascii码，z 字符重复次数，sx 字符属性

    mov ah,2 
    mov bh,0
    mov dh,x
    mov dl,y
    int 10h

    mov ah,9 
    mov bh,0
    mov bl,sx
    mov al,as
    mov cx,z
    int 10h

    endm




main proc far
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码

    mov ah,6  ;初始化背景底色
    mov al,0
    mov ch,0
    mov cl,0
    mov dh,24
    mov dl,79
    mov bh,2eH ;青底黄字
    int 10h

    mov ah,6   ;初始化横向车道
    mov al,0
    mov ch,9
    mov cl,0
    mov dh,15
    mov dl,79
    mov bh,70h   ;浅灰色车道
    int 10h

    mov ah,6   ;初始化竖向车道
    mov al,0
    mov ch,0
    mov cl,33
    mov dh,24
    mov dl,45
    mov bh,70h  ;浅灰色车道
    int 10h

    ;横向
    Pain 12,0,'-',33,7eh  ;绘制车道中线
    Pain 12,46,'-',34,7eh

    ;竖向
    Pain 0,39,'|',1,7eh
    Pain 1,39,'|',1,7eh
    Pain 2,39,'|',1,7eh
    Pain 3,39,'|',1,7eh
    Pain 4,39,'|',1,7eh
    Pain 5,39,'|',1,7eh
    Pain 6,39,'|',1,7eh
    Pain 7,39,'|',1,7eh
    Pain 8,39,'|',1,7eh

    Pain 16,39,'|',1,7eh
    Pain 17,39,'|',1,7eh
    Pain 18,39,'|',1,7eh
    Pain 19,39,'|',1,7eh
    Pain 20,39,'|',1,7eh
    Pain 21,39,'|',1,7eh
    Pain 22,39,'|',1,7eh
    Pain 23,39,'|',1,7eh
    Pain 24,39,'|',1,7eh


    mov ah,1   ;隐藏光标
    mov ch,32
    int 10h


    call lightmode1_1 ;初始时为模式1
    mov cx,30
L:
    call JudgeMode
    mov cx,30
    call showtime
    call carmove1
    call carmove2
    call carmove3
    call carmove4
    call carmove5
    call carmove6   
    dec count
    DELAY 20
    cmp count,1
    jnz s2
    mov count,30
    inc mark
    s2:
    loop L



    mov ah,1
    int 21h

    MOV AH,4CH
    INT 21H
main endp


;开车
carmove1 proc near   ;1号车启动
    push ax
	push bx
	push cx
	push dx


    call Earse1
    call car1
    cmp car1X,9
    jnz exit
    cmp mode,1 ;根据模式号判断，当1，3路口为红灯时，行标-1则每次都在原地画车
    jz exit
    dec car1X


exit:
    pop dx
	pop cx
	pop bx
	pop ax
	ret

carmove1 endp


car1 proc near  ;1号小车运行
    push ax
	push bx
	push cx
	push dx

    mov ah,2
    mov bh,0
    mov dh,car1X
    mov dl,car1Y
    int 10h

    mov ah,9
    mov bh,0
    mov bl,49h ;红色小车
    mov al,'a'
    mov cx,1
    int 10h

    inc car1X
    cmp car1X,24
    jnz exit1
    call Earse1
    mov car1X,0

exit1:pop dx
	pop cx
	pop bx
	pop ax
	ret
car1 endp

Earse1 proc near  ;擦除1号小车之前的轨迹
    push ax
	push bx
	push cx
	push dx

    mov bl,car1X
    dec bl

    mov ah,6
    mov al,0
    mov ch,bl
    mov cl,35
    mov dh,bl
    mov dl,35
    mov bh,70h
    int 10h

    pop dx
	pop cx
	pop bx
	pop ax
	ret
Earse1 endp

carmove2 proc near  ;2号车启动
    push ax
	push bx
	push cx
	push dx

    call Earse2
    call car2

    cmp car2Y,44
    jnz exit2
    cmp mode,2  ;横道车像素要减2，根据模式号来判断
    jz exit2
    inc car2Y
    inc car2Y

exit2:pop dx
	pop cx
	pop bx
	pop ax
	ret
carmove2 endp


car2 proc near   ;2号小车运行
    push ax
	push bx
	push cx
	push dx

    mov ah,2
    mov bh,0
    mov dh,car2X
    mov dl,car2Y
    int 10h

    mov ah,9
    mov bh,0
    mov bl,14h ;蓝色小车
    mov al,'b'
    mov cx,1
    int 10h

    dec car2Y
    dec car2Y
    cmp car2Y,0
    jg exit3
    call Earse2
    mov car2Y,78

exit3:pop dx
	pop cx
	pop bx
	pop ax
	ret
car2 endp

Earse2 proc near  ;擦除2号车轨迹
    push ax
	push bx
	push cx
	push dx

    mov bl,car2Y
    inc bl
    inc bl

    mov ah,6
    mov al,0
    mov ch,car2X
    mov cl,bl
    mov dh,car2X
    mov dl,bl
    mov bh,70h
    int 10h

    pop dx
	pop cx
	pop bx
	pop ax
	ret
Earse2 endp

carmove3 proc near  ;3号车启动
    push ax
	push bx
	push cx
	push dx

    call Earse3
    call car3
    cmp car3X,15
    jnz exit4
    cmp mode,1 ;同1号车
    jz exit4
    inc car3X

exit4:pop dx
	pop cx
	pop bx
	pop ax
	ret
carmove3 endp


car3 proc near  ;3号车运行
    push ax
	push bx
	push cx
	push dx

    mov ah,2
    mov bh,0
    mov dh,car3X
    mov dl,car3Y
    int 10h

    mov ah,9
    mov bh,0
    mov bl,0e1h  ;黄色小车
    mov al,'c'
    mov cx,1
    int 10h

    dec car3X
    cmp car3X,0
    jnz exit5
    call Earse3
    mov car3X,24

exit5:pop dx
	pop cx
	pop bx
	pop ax
	ret
car3 endp

Earse3 proc near  ;擦除3号车轨迹
    push ax
	push bx
	push cx
	push dx

    mov bl,car3X
    inc bl   

    mov ah,6
    mov al,0
    mov ch,bl
    mov cl,car3Y
    mov dh,bl
    mov dl,car3Y
    mov bh,70h
    int 10h

    pop dx
	pop cx
	pop bx
	pop ax
	ret
Earse3 endp

carmove4 proc near   ;4号车启动
    push ax
	push bx
	push cx
	push dx

	call Earse4
	call car4

	cmp car4Y,34
	jnz exit6
    cmp mode,2
    jz exit6
    dec car4Y
    dec car4Y

exit6:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
carmove4 endp

car4 proc near    ;4号车运行
    push ax
	push bx
	push cx
	push dx

    mov ah,2
    mov bh,0
    mov dh,car4X
    mov dl,car4Y
    int 10h

    mov ah,9
    mov bh,0
    mov bl,24h ;绿色小车
    mov al,'d'
    mov cx,1
    int 10h

    inc car4Y
    inc car4Y
    cmp car4Y,78
    jnz exit7
    call Earse4
    mov car4Y,0

exit7:pop dx
	pop cx
	pop bx
	pop ax
	ret
car4 endp

Earse4 proc near  ;擦除4号车轨迹
    push ax
	push bx
	push cx
	push dx


    mov bl,car4Y
    dec bl
    dec bl

    mov ah,6
    mov al,0
    mov ch,car4X
    mov cl,bl
    mov dh,car4X
    mov dl,bl
    mov bh,70h
    int 10h

    pop dx
	pop cx
	pop bx
	pop ax
	ret
Earse4 endp

carmove5 proc near ;5号车启动
    push ax
	push bx
	push cx
	push dx

    call Earse5
    call car5

    pop dx
	pop cx
	pop bx
	pop ax
	ret
carmove5 endp

car5 proc near  ;5号车运行
    push ax
	push bx
	push cx
	push dx

    mov ah,2
    mov bh,0
    mov dh,car5X
    mov dl,car5Y
    int 10h

    mov ah,9
    mov bh,0
    mov bl,34h ;绿色小车
    mov al,'e'
    mov cx,1
    int 10h

    cmp car5X,14   ;判断转向条件
    jnz straight

    inc car5Y
    inc car5Y

    cmp car5Y,79  
    jnz exit8
    call Earse5
    mov car5X,24
    mov car5Y,43
    jmp exit8

straight:
    dec car5X

exit8:
    pop dx
	pop cx
	pop bx
	pop ax
	ret
car5 endp

Earse5 proc near  ;擦除5号车轨迹(分为转向了和没转向）
    push ax
	push bx
	push cx
	push dx

    cmp car5Y,43
    jnz  turn

    mov bl,car5X
    inc bl

    mov ah,6
    mov al,0
    mov ch,bl
    mov cl,car5Y
    mov dh,bl
    mov dl,car5Y
    mov bh,70h
    int 10h

    jmp exit9

turn:
    mov bl,car5Y
    dec bl
    dec bl

    mov ah,6
    mov al,0
    mov ch,car5X
    mov cl,bl
    mov dh,car5X
    mov dl,bl
    mov bh,70h
    int 10h

exit9:
    pop dx
	pop cx
	pop bx
	pop ax
	ret
Earse5 endp

carmove6 proc near ;6号车启动
    push ax
	push bx
	push cx
	push dx

    call Earse6
    call car6
     cmp car6X,9
    jnz exit13
    cmp mode,1 
    jz exit13
    dec car6X

exit13:    
    pop dx
	pop cx
	pop bx
	pop ax
	ret
carmove6 endp

car6 proc near  ;6号车运行
    push ax
	push bx
	push cx
	push dx

    mov ah,2
    mov bh,0
    mov dh,car6x
    mov dl,car6Y
    int 10h

    mov ah,9
    mov bh,0
    mov bl,0fh ;黑色小车
    mov al,'f'
    mov cx,1
    int 10h

    cmp car6x,13   ;判断转向条件
    jnz straight

    inc car6Y
    inc car6Y

    cmp car6Y,79  
    jnz exit11
    call Earse6
    mov car6X,0
    mov car6Y,37
    jmp exit11

straight:
    inc car6x

exit11:
    pop dx
	pop cx
	pop bx
	pop ax
	ret
car6 endp

Earse6 proc near  ;擦除6号车轨迹(分为转向了和没转向）
    push ax
	push bx
	push cx
	push dx

    cmp car6Y,37
    jnz  turn

    mov bl,car6X
    dec bl

    mov ah,6
    mov al,0
    mov ch,bl
    mov cl,car6Y
    mov dh,bl
    mov dl,car6Y
    mov bh,70h
    int 10h

    jmp exit12

turn:
    mov bl,car6Y
    dec bl
    dec bl

    mov ah,6
    mov al,0
    mov ch,car6X
    mov cl,bl
    mov dh,car6X
    mov dl,bl
    mov bh,70h
    int 10h

exit12:
    pop dx
	pop cx
	pop bx
	pop ax
	ret
Earse6 endp

showtime proc near   ;在十字路口中心显示时间
    push ax
	push bx
	push cx
	push dx


    call time1
    call time2

    pop dx
	pop cx
	pop bx
	pop ax
	ret
showtime endp

time1 proc near  ;显示时间十位
    push ax
	push bx
	push cx
	push dx

    mov bl,10
    mov al,count
    cbw
    div bl

    mov ah,2
    mov bh,0
    mov dh,12
    mov dl,39
    int 10h


    mov ah,9
    mov bh,0
    mov bl,7eh
    or  al,30h
    mov cx,1
    int 10h

    pop dx
	pop cx
	pop bx
	pop ax
	ret
time1 endp

time2 proc near  ;显示时间个位
    push ax
	push bx
	push cx
	push dx

    mov bl,10
    mov al,count
    cbw
    div bl
    mov al,ah

    mov ah,2
    mov bh,0
    mov dh,12
    mov dl,40
    int 10h


    mov ah,9
    mov bh,0
    mov bl,7eh
    or  al,30h
    mov cx,1
    int 10h

    pop dx
	pop cx
	pop bx
	pop ax
	ret
time2 endp

;设置路口模式,可以分为两种模式  （从北开始顺时针各个路口分别编号为1、2、3、4）
;模式一：南北通行 （信号灯包含两种模式）
;模式二：东西通行（信号灯包含两种模式）
lightmode1_1 proc near
    push ax
	push bx
	push cx
	push dx

    light1 gray,gray,green
    light3 gray,gray,green

    light2 red,gray,gray
    light4 red,gray,gray

    pop dx
	pop cx
	pop bx
	pop ax
	ret
lightmode1_1 endp

lightmode1_2 proc near
    push ax
	push bx
	push cx
	push dx

    light1 gray,yellow,gray
    light3 gray,yellow,gray

    light2 red,gray,gray
    light4 red,gray,gray

    pop dx
	pop cx
	pop bx
	pop ax
	ret
lightmode1_2 endp

lightmode2_1 proc near
    push ax
	push bx
	push cx
	push dx

    light1 red,gray,gray
    light3 red,gray,gray

    light2 gray,gray,green
    light4 gray,gray,green

    pop dx
	pop cx
	pop bx
	pop ax
	ret
lightmode2_1 endp

lightmode2_2 proc near
    push ax
	push bx
	push cx
	push dx

    light1 red,gray,gray
    light3 red,gray,gray

    light2 gray,yellow,gray
    light4 gray,yellow,gray

    pop dx
	pop cx
	pop bx
	pop ax
	ret
lightmode2_2 endp

JudgeMode proc near  ;判断红绿灯模式
    push ax
	push bx
	push cx
	push dx

    ;判断奇偶   奇数为模式1  偶数为模式2
    test mark,1
    jz two

one:cmp count,10   ;≤10秒时改为黄灯（2，4不变）
    ja  M1
    call lightmode1_2
    jmp exit10
    mov mode,1

M1: call lightmode1_1
    mov mode,1
    jmp exit10

two:cmp  count,10 ;≤10秒时改为黄灯（1，3不变）
    ja M2
    call lightmode2_2
    jmp exit10
    mov mode,2
M2: call lightmode2_1
    mov mode,2
    jmp exit10


exit10:
    pop dx
	pop cx
	pop bx
	pop ax
	ret
JudgeMode endp

CODES ENDS
    END main





