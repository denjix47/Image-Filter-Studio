# Image Filter Studio

A console-based, object-oriented C++ application designed to apply customizable filter pipelines to images. The system features a robust role-based architecture, allowing for administrative oversight and a secure customer portal for image processing. 

Developed as a semester project at FAST NUCES Islamabad.

## System Features

| Feature | Description | Access Level |
| :--- | :--- | :--- |
| **Role-Based Access** | Distinct login portals and functionalities for system users. | Admin & Customer |
| **Custom Pipelines** | Ability to stack multiple filters sequentially (e.g., Grayscale -> Blur -> Invert). | Customer |
| **Secure Authentication** | Strict CNIC validation (13 digits) and complex password requirements. | Admin & Customer |
| **Account Security** | Three-attempt lockout protocol and manual account blocking. | Admin |
| **Session Management** | Automatically tracks session counts and logs filter pipeline history. | System |
| **Automated I/O** | Processed images are auto-saved and time-stamped (`CNIC_YYYYMMDD_HHMMSS.png`). | System |

## Available Filters

The studio supports a dynamically managed catalog of ten distinct image processing filters:

| ID | Filter Name | Description |
| :--- | :--- | :--- |
| 1 | **Grayscale** | Converts the image to black and white by balancing RGB channels. |
| 2 | **Invert** | Inverts the color values to create a negative effect. |
| 3 | **Brightness Adjust** | Modifies the overall brightness based on user input (-100 to +100). |
| 4 | **Contrast Stretch** | Normalizes and stretches contrast to utilize the full color spectrum. |
| 5 | **Red Channel Only** | Isolates the red color channel, zeroing out green and blue. |
| 6 | **Green Channel Only**| Isolates the green color channel, zeroing out red and blue. |
| 7 | **Blue Channel Only** | Isolates the blue color channel, zeroing out red and green. |
| 8 | **Box Blur (3x3)** | Applies a spatial low-pass filter to blur the image using a 3x3 kernel. |
| 9 | **Flip Horizontal** | Mirrors the image across its vertical axis. |
| 10 | **Flip Vertical** | Mirrors the image across its horizontal axis. |

## Project Architecture

The application is structured around Object-Oriented Programming (OOP) principles, separating concerns into distinct modules.

| Module Type | Core Files | Primary Responsibility |
| :--- | :--- | :--- |
| **Core Entities** | `User.h/cpp`, `Admin.h/cpp`, `Customer.h/cpp` | Defines user attributes, authentication, and access privileges. |
| **Image Handling**| `Image.h/cpp`, `Pixel.h/cpp` | Manages the image buffer, individual RGB values, and file I/O operations. |
| **Data Managers** | `CustomerManager.h/cpp`, `CatalogManager.h/cpp` | Handles persistence, loading, searching, and state of users and filters. |
| **Session Logic** | `SessionManager.h/cpp` | Logs and retrieves the history of filter pipelines applied by users. |
| **Filter Engine** | `Filter.h/cpp`, `FilterSession.h/cpp` | Acts as the pipeline manager, queuing and applying filters to an image. |
| **Implementations**| `Grayscale.cpp`, `BoxBlur.cpp`, etc. | Contains the specific algorithms for each distinct filter operation. |

## Getting Started

### Prerequisites
* A standard C++ compiler (e.g., GCC/MinGW).
* The `stb_image` libraries (`stb_image.h` and `stb_image_write.h`) must be present in the root directory for image I/O operations.

### Compilation

To compile the project via the terminal, navigate to the project directory and compile all `.cpp` files:

```bash
g++ *.cpp -o filter_studio
```


## Execution

Run the compiled executable:

```Bash
# On Windows
filter_studio.exe

# On Linux/macOS
./filter_studio
```
## Authors

Sameer Majid FAST-NUCES | CS1004 — Object Oriented Programming | Spring 2026
