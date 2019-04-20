# OS_2_2019
ETU"LETI" OS 2019 
- Làm quen với các công cụ đồng bộ hóa thread - nhị phân và semaphore không định danh; cùng với các lệnh gọi hệ thống (system calls) để: tạo (create), đóng (close/finish), chụp (capture), giải phóng (release) mutex và semaphores không định danh.
# СИНХРОНИЗАЦИЯ ПОТОКОВ С ПОМОЩЬЮ МЬЮТЕКСОВ И НЕИМЕНОВАННЫХ СЕМАФОРОВ  (ĐỒNG BỘ HÓA SỬ DỤNG MUTEX VÀ SEMAPHORES VÔ DANH)  
# Mục đích bài lab:  
Làm quen với công cụ đồng bộ hóa threads - semaphore nhị phân và semaphore vô danh. Làm quen với các lệnh hệ thống, đảm bảo việc create, close, capture, release mutex và semaphore vô danh (unnamed).  
## Lý thuyết  
* Để các threads thực hiện mutual exclusion (loại trừ lẫn nhau) khi truy cập (compete) vào cùng một critical resourse (tài nguyên quan trọng), chúng ta sử dụng semaphore.  
*Semaphore*: Semaphore is a technique for synchronizing two/more task competing for the same resources. When a task wants to use a resource, it requests for the semaphore and will be allocated if the semaphore is available. If the semaphore is not available then the requesting task will go to blocked state till the semaphore becomes free.  
