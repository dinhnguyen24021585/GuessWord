# GuessWord
 
1. Họ và tên : Bùi Đình Nguyên
   Mã sinh viên : 24021585

2. Game và chủ đề game: Tên game của em là Đuổi hình bắt chữ. Game này đơn thuần chỉ là game giải đố thông thường, đoán ý nghĩa của bức tranh câu hỏi muốn đề cập để đưa ra đáp án

3. Ngưỡng điểm em cho là xứng đáng với game của em : 5

4. Lý do bảo vệ ngưỡng điểm trên:
- Phần lớn code em tham khảo khung chung của file Tài liệu bố sung rồi tự phát triển thêm
- Phần nhỏ tham khảo trang Lazyfoo (phần gõ đáp án (text): https://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php), tham khảo ChatGPT để in ra cửa sổ chữ Tiếng Việt (thay vì dùng TTF_RenderSolid thì dùng TTF_RenderUTF8_Blended)
- Có dùng các lệnh vẽ hình cơ bản
- Có dùng Texture
- Có dùng background, background trôi
- Dùng cả event bàn phím và chuột
- Có dùng sound nhưng chỉ có sound khi trả lời đúng và sai
- Không có nhạc nền
- Dùng font chữ: TNH-Xuồng (font chữ được lấy cảm hứng từ những chiếc xuồng ba lá của đồng bào Miền Tây)
- Menu đơn giản, gọn
- Có các nút: Home: quay về menu,Replay: chơi lại màn đó (gõ lại đáp án từ đầu)
- Thuật đã cài:
+ Check đáp án: Check cả cụm từ đã gõ khi người chơi xác nhận đáp án (nhấn Enter)
+ Random tọa độ của mây trong khoảng
+ Check các sự kiện bàn phím mà người chơi có thể nhập vào game
+ Căn lề giữa cho đáp án được nhập vào hiện lên game
- Nhược điểm của game:
+ Khá sơ sài
+ Nhiều thuật toán ngây ngô, chắp vá nhiều, đơn giản (check cụm từ có giống với đáp án hay không)
+ Thoát game phải chơi lại từ đầu (chưa có tính năng save game do có ít level (6))
+ Chưa hỗ trợ viết Tiếng Việt

5: Link Gameplay: https://youtu.be/ggcstr4a4qY