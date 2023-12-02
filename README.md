# PROJECT DESIGN PATTERN

------------------

## RULES FOR PROJECT DESIGN PATTERN

### 1. Requirement

Each group choose two patterns:

* A structural pattern : Adapter
* A behavioral pattern : Mediator

Present the patterns and record your presentation into video (duration: 10’ - 30’)

### 2. Submission

Save your project into a folder on your cloud (google drive or onedrive). The folder includes:

* **Slide:** [group]-[mssvs].pptx or pdf
* **Report:** [group]-[mssvs].docx or pdf
* **Video:** [group]-[mssvs].mp4
* **Source code**

Group leader submit the link to the folder through Moodle.

### 3. Assessment

| Item    | Ratio |
| ------- | ----- |
| Content |  50%  |
| Video   |  25%  |
| Slide   |  25%  |

------------------

## LECTURE OF PROJECT DESSIGN PATTERN

### 1. Definition

**Adapter** là mẫu thiết kế cấu trúc cho phép các đối tượng có giao diện không tương thích cộng tác. (**Adapter** is a *structural* design pattern that allows objects with incompatible interfaces to collaborate.)

![adapter](https://refactoring.guru/images/patterns/content/adapter/adapter-en.png)

### 2. Problem

**Ví dụ 1:**
Hãy tưởng tượng bạn đang tạo một ***ứng dụng*** theo dõi thị trường chứng khoán. Ứng dụng tải xuống dữ liệu chứng khoán từ nhiều nguồn ở định dạng XML, sau đó hiển thị các biểu đồ và sơ đồ đẹp mắt cho người dùng.

![adapter](https://refactoring.guru/images/patterns/diagrams/adapter/problem-en-2x.png)

Tại một thời điểm nào đó, bạn quyết định cải thiện ứng dụng bằng cách tích hợp thư viện phân tích thông minh của bên thứ 3. Nhưng có một nhược điểm: thư viện phân tích chỉ hoạt động với dữ liệu ở định dạng JSON. Bạn có thể thay đổi thư viện để hoạt động với XML. Tuy nhiên, điều này có thể phá vỡ cấu trúc một số mã hiện có dựa trên thư viện. Và tệ hơn, bạn có thể không có quyền truy cập vào mã nguồn của thư viện ngay từ đầu, khiến phương pháp này không thể thực hiện được.

**Ví dụ 2:**
Trong thực tế, có rất nhiều loại phích cắm điện với đa dạng chủng loại và thiết kế. Tùy vào đất nước và mục đích sử dụng của từng cá nhân và tổ chức khác nhau.
Ở Việt Nam thường sử dụng cách loại phích cắm điện có 2 chân để phù hợp với ổ điện có hai lỗ cắm. Tuy nhiên, nếu một ngày bạn đi du lịch qua các nước Mỹ Âu vả bạn nhận ra tại đây mọi người đều sử dụng các loại phích cắm điện 3 chân và ổ cắm điện cũng không phù hợp với loại bạn đang dùng ở Việt Nam và trong hoàn cảnh đó chiếc Laptop của bạn đang cần sạc Pin gấp thì bạn nên xử lý như thế nào?

![ex2](https://refactoring.guru/images/patterns/content/adapter/adapter-comic-1-en.png)

### 3. Solution

Bạn có thể tạo một bộ chuyển đổi (***adapter***). Đây là một đối tượng đặc biệt có chức năng chuyển đổi giao diện của một đối tượng để đối tượng khác có thể hiểu được.

Bộ ***adapter*** bao bọc (wraps) một trong các đối tượng để che giấu sự phức tạp của quá trình chuyển đổi diễn ra ở hậu trường. Đối tượng được bao bọc thậm chí không nhận biết được bộ chuyển đổi. Ví dụ: bạn có thể bao bọc một đối tượng hoạt động theo đơn vị mét và kilômét bằng một bộ chuyển đổi có khả năng chuyển đổi tất cả dữ liệu sang các đơn vị đo lường Anh như feet và dặm.

Bộ ***adapter*** không chỉ có thể chuyển đổi dữ liệu sang nhiều định dạng khác nhau mà còn có thể giúp các đối tượng có giao diện khác nhau cộng tác với nhau. Đây là cách nó hoạt động:

1. Bộ ***adapter*** có giao diện tương thích với một trong các đối tượng hiện có.
2. Sử dụng giao diện này, đối tượng hiện có có thể gọi các phương thức của bộ điều hợp một cách an toàn.
3. Khi nhận được cuộc gọi, bộ ***adapter*** sẽ chuyển yêu cầu đến đối tượng thứ hai nhưng theo định dạng và thứ tự mà đối tượng thứ hai mong đợi.

Đôi khi, thậm chí có thể tạo bộ adapter hai chiều có thể chuyển đổi cuộc gọi theo cả hai hướng.

![adapter](https://refactoring.guru/images/patterns/diagrams/adapter/solution-en-2x.png)

Hãy quay lại ứng dụng thị trường chứng khoán trong ví dụ 1 . Để giải quyết vấn đề nan giải về các định dạng không tương thích, ta có thể tạo bộ chuyển đổi XML sang JSON cho mọi lớp của thư viện phân tích mà mã của ta làm việc trực tiếp. Sau đó, ta điều chỉnh mã của mình để chỉ giao tiếp với thư viện thông qua các bộ ***adapter*** này. Khi bộ điều hợp nhận được lệnh gọi, nó sẽ dịch dữ liệu XML đến thành cấu trúc JSON và chuyển lệnh gọi đó đến các phương thức thích hợp của đối tượng phân tích được bao bọc.

### 4. Structure

#### 4.1. Object Adapter

Việc triển khai này sử dụng nguyên lý thành phần đối tượng: bộ ***adapter*** triển khai giao diện của một đối tượng và bao bọc đối tượng kia. Nó có thể được thực hiện bằng tất cả các ngôn ngữ lập trình phổ biến.

![objectAdapter](https://refactoring.guru/images/patterns/diagrams/adapter/structure-object-adapter-indexed.png)

1. ***Client*** là lớp chứa logic nghiệp vụ (*business logic*) hiện có của chương trình.
2. ***Client Interface*** là giao diện của ***client*** mà bộ ***adapter*** sẽ triển khai. Nó mô tả một giao thức mà các lớp khác phải tuân theo để có thể cộng tác với code của Client.
3. ***Service*** là một số lớp hữu ích (thường là bên thứ 3 hoặc kế thừa). ***Client*** không thể sử dụng trực tiếp lớp này vì nó có giao diện không tương thích.
4. ***Adapter*** là một lớp có thể hoạt động với cả ***Client*** và ***Service*** : nó triển khai ***Client Interfaces*** trong khi bao bọc đối tượng ***Service***. ***Adapter*** nhận lời gọi từ máy khách thông qua giao diện máy khách và chuyển chúng thành cuộc gọi đến đối tượng dịch vụ được bao bọc theo định dạng mà nó có thể hiểu được.
5. Code của ***Client*** không được ghép nối với lớp ***Adapter*** cụ thể miễn là nó hoạt động thông qua giao diện ***Client***. Nhờ vậy, bạn có thể đưa vào chương trình nhiều lớp ***Adapter*** khác nhau mà không cần thay đổi code của ***Client*** (Không vi phạm code của ***Client***  hiện có). Điều này có thể hữu ích khi giao diện của lớp ***Service*** bị thay đổi hoặc thay thế: bạn chỉ có thể tạo một lớp ***Adapter*** mới mà không cần thay đổi code của ***Client***.

#### 4.2. Class Adapter

Việc triển khai này sử dụng tính kế thừa: **Adapter** kế thừa giao diện từ cả hai đối tượng cùng một lúc. Lưu ý rằng phương pháp này chỉ có thể được triển khai bằng các ngôn ngữ lập trình hỗ trợ đa kế thừa, chẳng hạn như C++.

![classAdapter](https://refactoring.guru/images/patterns/diagrams/adapter/structure-class-adapter-indexed.png)

Bộ điều hợp lớp không cần bọc bất kỳ đối tượng nào vì nó kế thừa các hành vi từ cả máy khách và dịch vụ. Sự thích ứng xảy ra trong các phương thức được ghi đè. Bộ điều hợp kết quả có thể được sử dụng thay cho lớp máy khách hiện có.

### 5. Application

* Sử dụng lớp Adapter khi bạn muốn sử dụng một số lớp hiện có nhưng giao diện của nó không tương thích với phần còn lại của mã.
  
  * Mẫu ***Adapter*** cho phép bạn tạo một lớp middle-layer đóng vai trò là bộ dịch giữa code của bạn và lớp kế thừa, lớp của bên thứ 3 hoặc bất kỳ lớp nào khác có giao diện lạ

* Sử dụng mẫu này khi bạn muốn sử dụng lại một số lớp con hiện có thiếu một số chức năng phổ biến không thể thêm vào lớp cha.

  * Bạn có thể mở rộng từng lớp con và đưa chức năng còn thiếu vào các lớp con mới. Tuy nhiên, bạn sẽ cần phải sao chép mã trên tất cả các lớp mới này, điều này có vẻ rất tệ.
  * Giải pháp tinh tế hon nhiều là có thể đặt các chức năng này vào một lớp ***Adapter*** đơn lẻ. Bây giờ các lớp con có thể kế thừa từ lớp ***Adapter*** và có tất cả các chức năng mà chúng cần.

### 6. Implementation

------------------

## ASSIGNMENT TASKS

| Student ID | Full name       | Group | Task    | Notes |
| ---------- | ----------------| ----- | --------| ------|
| 22127174   | Ngo Van Khai    |       |         |       |
| 22127322   | Le Phuoc Phat   |       |         |       |
| 22127388   | To Quoc Thanh   |       |         |       |
| 22127441   | Thai Huyen Tung |       |         |       |
