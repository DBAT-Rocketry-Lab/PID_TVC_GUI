import customtkinter as ctk
import socket
import math

# =====================================================
# SETTINGS
# =====================================================

ESP32_IP = "192.168.1.123"
ESP32_PORT = 5000

MAX_GIMBAL_RAD = 0.087   # maximum gimbal angle allowed ~ 5 degrees (0.087 radians)

# =====================================================
# NETWORK
# =====================================================

sock = None   # initializing sock variable


def connect_to_esp():
    global sock    # globalizing that sock variable to use it in this function

    try:
        sock = socket.socket(
            socket.AF_INET,     # means IPv4
            socket.SOCK_STREAM  # means TCP protocol
        )

        sock.connect(
            (ESP32_IP, ESP32_PORT)    # connect to this IP on this PORT
        )

        status_label.configure(
                text="CONNECTED"       # if it successfully connects--- then status_label.confugure() returns the desired output of try:.. 
        )

    except Exception as e:        # if it doesnt connect
        status_label.configure(
            text=f"ERROR: {e}"
        )


# =====================================================
# COMMAND SEND
# =====================================================

pitch_cmd = 0.0
yaw_cmd = 0.0
throttle_cmd = 0.0


def send_command():

    global sock

    if sock is None:
        return

    try:

        packet = (
            f"{throttle_cmd:.3f},"
            f"{pitch_cmd:.4f},"
            f"{yaw_cmd:.4f}\n"
        )

        sock.send(packet.encode())

    except:
        pass


# =====================================================
# THROTTLE
# =====================================================

def throttle_changed(value):

    global throttle_cmd

    throttle_cmd = float(value)

    throttle_percent.configure(
        text=f"{int(value*100)}%"
    )

    send_command()


# =====================================================
# JOYSTICK
# =====================================================

CANVAS_SIZE = 300
CENTER = CANVAS_SIZE // 2
RADIUS = 100

stick_x = CENTER
stick_y = CENTER


def update_joystick(event):

    global stick_x
    global stick_y

    dx = event.x - CENTER
    dy = event.y - CENTER

    distance = math.sqrt(
        dx * dx + dy * dy
    )

    if distance > RADIUS:

        scale = RADIUS / distance

        dx *= scale
        dy *= scale

    stick_x = CENTER + dx
    stick_y = CENTER + dy

    draw_joystick()

    update_gimbal(dx, dy)


def release_joystick(event):

    global stick_x
    global stick_y

    stick_x = CENTER
    stick_y = CENTER

    draw_joystick()

    update_gimbal(0, 0)


def update_gimbal(dx, dy):

    global pitch_cmd
    global yaw_cmd

    yaw_cmd = (
        dx / RADIUS
    ) * MAX_GIMBAL_RAD

    pitch_cmd = (
        -dy / RADIUS
    ) * MAX_GIMBAL_RAD

    pitch_label.configure(
        text=f"Pitch: {pitch_cmd:.4f} rad"
    )

    yaw_label.configure(
        text=f"Yaw: {yaw_cmd:.4f} rad"
    )

    send_command()


def draw_joystick():

    canvas.delete("all")

    canvas.create_oval(
        CENTER-RADIUS,
        CENTER-RADIUS,
        CENTER+RADIUS,
        CENTER+RADIUS
    )

    canvas.create_line(
        CENTER,
        CENTER-RADIUS,
        CENTER,
        CENTER+RADIUS
    )

    canvas.create_line(
        CENTER-RADIUS,
        CENTER,
        CENTER+RADIUS,
        CENTER
    )

    canvas.create_oval(
        stick_x-12,
        stick_y-12,
        stick_x+12,
        stick_y+12,
        fill="red"
    )


# =====================================================
# GUI
# =====================================================

ctk.set_appearance_mode("dark")

app = ctk.CTk()

app.geometry("700x700")

app.title(
    "TVC Ground Control Station"
)

# =====================================================
# CONNECTION
# =====================================================

top_frame = ctk.CTkFrame(app)
top_frame.pack(
    fill="x",
    padx=10,
    pady=10
)

connect_button = ctk.CTkButton(
    top_frame,
    text="Connect",
    command=connect_to_esp
)

connect_button.pack(
    side="left",
    padx=10
)

status_label = ctk.CTkLabel(
    top_frame,
    text="DISCONNECTED"
)

status_label.pack(
    side="left",
    padx=20
)

# =====================================================
# JOYSTICK
# =====================================================

canvas = ctk.CTkCanvas(
    app,
    width=CANVAS_SIZE,
    height=CANVAS_SIZE
)

canvas.pack(
    pady=20
)

draw_joystick()

canvas.bind(
    "<B1-Motion>",
    update_joystick
)

canvas.bind(
    "<ButtonRelease-1>",
    release_joystick
)

# =====================================================
# TELEMETRY
# =====================================================

pitch_label = ctk.CTkLabel(
    app,
    text="Pitch: 0.0000 rad"
)

pitch_label.pack()

yaw_label = ctk.CTkLabel(
    app,
    text="Yaw: 0.0000 rad"
)

yaw_label.pack()

# =====================================================
# THROTTLE
# =====================================================

throttle_frame = ctk.CTkFrame(app)
throttle_frame.pack(
    fill="x",
    padx=20,
    pady=20
)

ctk.CTkLabel(
    throttle_frame,
    text="Throttle"
).pack()

throttle_slider = ctk.CTkSlider(
    throttle_frame,
    from_=0,
    to=1,
    command=throttle_changed
)

throttle_slider.pack(
    fill="x",
    padx=20,
    pady=10
)

throttle_percent = ctk.CTkLabel(
    throttle_frame,
    text="0%"
)

throttle_percent.pack()

# =====================================================

app.mainloop()
