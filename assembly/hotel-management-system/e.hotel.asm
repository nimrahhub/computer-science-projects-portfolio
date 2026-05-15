org 100h  ; Start of the program

; Data Section
.data
    ; Modified welcome message with centered text in rectangle
    top_border    db '----------------------------------------$'
    welcome_msg   db '           WELCOME TO OUR HOTEL  $'        ; Added spaces for centering
    bottom_border db '----------------------------------------$'
    wifi_msg      db '***********FREE WIFI AVAILABLE**********$'
    
    enter_id_msg db 'Please enter your ID number (13 digits): $'
    enter_name_msg db 'Please enter your name: $'
    enter_date_msg db 'Enter booking date (dd/mm): $'
    view_rooms_msg db 'View our available rooms:$'
    room1_msg db '1. Economy   - 10000 per night$'
    room2_msg db '2. Suite     - 15000 per night$'
    room3_msg db '3. Penthouse - 25000 per night$'
    cancel_booking_msg db 'Do you wish to cancel the booking? (y/n): $'
    choose_room_msg db 'Choose a room (1-3): $'
    nights_msg db 'How many nights would you like to stay? $'
    checkout_details_msg db 'Checkout Details:$'
    name_msg db 'Name: $'
    id_msg db 'ID: $'
    room_msg db 'Room: $'
    nights_stay_msg db 'Nights: $'
    room_services_msg db 'Room Services:$'
    lunch_msg db '1. Lunch - 2000$'
    dinner_msg db '2. Dinner - 2000$'
    tea_msg db '3. Tea - 1000$'
    housekeeping_msg db '4. Housekeeping - 500$'
    choose_service_msg db 'Choose a service (1-4), 0 to finish: $'
    service_cost_msg db 'Service Cost: $'
    rating_msg db 'Please rate our service ****** (1-5): $'
    star db '****************************************$'
    visit_again_msg db 'We hope to see you again soon!$'
    payment_option_msg db 'Choose payment method (1. Credit Card, 2. JazzCash, 3. EasyPaisa): $'
    payment_number_msg db 'Enter payment number: $'
    payment_pw_msg db 'Enter payment password: $'
    payment_confirmation_msg db 'Payment has been deducted. Thank you!$'
    cancel_sad_msg db 'We are sad to see you go. We hope to see you again soon!$'
    
    id_number db 13, ?, 13 dup('$')
    user_name db 20, ?, 20 dup('$')
    booking_date db 5, ?, 4 dup('$')
    room_choice db ?
    nights db ?
    service_choice db ?
    rating db ?
    payment_choice db ?
    payment_number db 16, ?, 16 dup('$')
    payment_password db 8, ?, 8 dup('$')
    service_cost dw 0  ; Initialize service_cost to 0

; Code Section
.code
start:
    ; Print welcome message in rectangle
    mov ah, 09h
    lea dx, top_border
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, welcome_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, bottom_border
    int 21h
    call new_line
    
    ; Print WiFi message
    mov ah, 09h
    lea dx, wifi_msg
    int 21h
    call new_line
    call new_line
    
    ; Prompt user to enter ID number
    mov ah, 09h
    lea dx, enter_id_msg
    int 21h
    
    mov ah, 0Ah
    lea dx, id_number
    int 21h
    call new_line
    
    ; Prompt user to enter name
    mov ah, 09h
    lea dx, enter_name_msg
    int 21h
    
    mov ah, 0Ah
    lea dx, user_name
    int 21h
    call new_line
    
    ; Prompt user to enter booking date
    mov ah, 09h
    lea dx, enter_date_msg
    int 21h
    
    mov ah, 0Ah
    lea dx, booking_date
    int 21h
    call new_line
    
    ; Print horizontal line after booking date
    mov ah, 09h
    lea dx, top_border
    int 21h
    call new_line
    
    ; Display available rooms
    mov ah, 09h
    lea dx, view_rooms_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, room1_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, room2_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, room3_msg
    int 21h
    call new_line
    
    ; Print horizontal line after room options
    mov ah, 09h
    lea dx, top_border
    int 21h
    call new_line
    
    ; Prompt user to choose a room
    mov ah, 09h
    lea dx, choose_room_msg
    int 21h
    
    mov ah, 01h
    int 21h
    sub al, '0'
    mov [room_choice], al
    call new_line
    
    ; Prompt user to enter number of nights
    mov ah, 09h
    lea dx, nights_msg
    int 21h
    
    mov ah, 01h
    int 21h
    sub al, '0'
    mov [nights], al
    
    ; Print Room Services on the next line
    call new_line
    mov ah, 09h
    lea dx, room_services_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, lunch_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, dinner_msg
    int 21h
    call 21h
    call new_line
    
    mov ah, 09h
    lea dx, tea_msg
    int 21h
    call new_line

    mov ah, 09h
    lea dx, housekeeping_msg
    int 21h
    call new_line

choose_services:
    mov ah, 09h
    lea dx, choose_service_msg
    int 21h
    
    mov ah, 01h
    int 21h
    sub al, '0'
    mov [service_choice], al
    
    cmp al, 0            ; If user presses 0 to finish
    je ask_cancel_booking ; Go to cancel booking prompt

    call calculate_service_cost
    call new_line
    
    mov ah, 09h
    lea dx, service_cost_msg
    int 21h
    mov ax, [service_cost]
    call print_number
    call new_line
    
    ; Continue with the services section
    jmp choose_services

ask_cancel_booking:
    ; Move to new line before asking for cancel confirmation
    call new_line
    mov ah, 09h
    lea dx, cancel_booking_msg  ; Change this message to ask if they want to cancel
    int 21h
    call new_line
    
    mov ah, 01h
    int 21h
    cmp al, 'y'             ; If the user presses 'y' (yes), cancel the booking
    je cancel_booking

    cmp al, 'n'             ; If the user presses 'n' (no), show checkout details
    je finish_services

cancel_booking:
    mov ah, 09h
    lea dx, cancel_sad_msg  ; Display cancellation message
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, star
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, visit_again_msg
    int 21h
    call new_line
    
    mov ah, 4Ch
    int 21h  ; Exit the program

finish_services:
    call new_line
    ; Print horizontal line before checkout details
    mov ah, 09h
    lea dx, top_border
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, checkout_details_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, name_msg
    int 21h
    lea dx, [user_name + 2]
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, id_msg
    int 21h
    lea dx, [id_number + 2]
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, room_msg
    int 21h
    mov dl, [room_choice]
    add dl, '0'
    mov ah, 02h
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, nights_stay_msg
    int 21h
    mov dl, [nights]
    add dl, '0'
    mov ah, 02h
    int 21h
    call new_line
    
    ; Print horizontal line before choose payment method
    mov ah, 09h
    lea dx, top_border
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, payment_option_msg
    int 21h
    
    mov ah, 01h
    int 21h
    sub al, '0'
    mov [payment_choice], al
    call new_line
    
    mov ah, 09h
    lea dx, payment_number_msg
    int 21h
    
    mov ah, 0Ah
    lea dx, payment_number
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, payment_pw_msg
    int 21h
    
    mov ah, 0Ah
    lea dx, payment_password
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, payment_confirmation_msg
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, rating_msg
    int 21h
    
    mov ah, 01h
    int 21h
    sub al, '0'
    mov [rating], al
    call new_line
    
    mov ah, 09h
    lea dx, star
    int 21h
    call new_line
    
    mov ah, 09h
    lea dx, visit_again_msg
    int 21h
    call new_line
    
    mov ah, 4Ch
    int 21h

new_line:
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    mov dl, 0Ah
    int 21h
    ret

calculate_service_cost:
    mov al, [service_choice]
    cmp al, 1
    je lunch
    cmp al, 2
    je dinner
    cmp al, 3
    je tea
    cmp al, 4
    je housekeeping
    jmp no_service
    
lunch:
    mov ax, 2000     ; 2000
    jmp store_service_cost
dinner:
    mov ax, 2000     ; 2000
    jmp store_service_cost
tea:
    mov ax, 1000     ; 1000
    jmp store_service_cost
housekeeping:
    mov ax, 500      ; 500
    jmp store_service_cost
    
no_service:
    mov ax, 0
    
store_service_cost:
    mov [service_cost], ax
    ret

print_number:
    mov cx, 0
    mov bx, 10
print_loop:
    xor dx, dx
    div bx
    push dx
    inc cx
    cmp ax, 0
    jne print_loop
print_digit:
    pop dx
    add dl, '0'
    mov ah, 02h
    int 21h
    loop print_digit
    ret
