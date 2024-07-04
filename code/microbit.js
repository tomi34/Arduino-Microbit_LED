let start_mls = 0
let timeout = 100 //maximum time the micro:bit will wait without getting data from the arduino in ms, change if needed (should match the arduino's timeout)
let timed_out = false
let data = ""
let a2_0 = 0
basic.forever(function () {
    if (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
        while (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
            pins.digitalWritePin(DigitalPin.P2, 1)
        }
        a2_0 = 0
        pins.digitalWritePin(DigitalPin.P2, 0)
    }
    if (pins.digitalReadPin(DigitalPin.P0) == 1) {
        pins.digitalWritePin(DigitalPin.P2, 0)
        data = ""
        timed_out = false
        start_mls = control.millis()
        pins.digitalWritePin(DigitalPin.P2, 1)
        while (pins.digitalReadPin(DigitalPin.P0) == 1) {
            if (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
                while (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
                    pins.digitalWritePin(DigitalPin.P2, 1)
                }
                break;
            }
            if (control.millis() >= start_mls + timeout * 0.75 && 0 == a2_0) {
                a2_0 = 1
                break;
            }
            if (control.millis() >= start_mls + timeout) {
                timed_out = true
            }
            if (timed_out) {
                pins.digitalWritePin(DigitalPin.P2, 1)
                break;
            }
        }
        pins.digitalWritePin(DigitalPin.P2, 0)
        for (let y = 0; y <= 4; y++) {
            if (timed_out) {
                pins.digitalWritePin(DigitalPin.P2, 1)
                break;
            }
            for (let x = 0; x <= 4; x++) {
                start_mls = control.millis()
                if (timed_out) {
                    pins.digitalWritePin(DigitalPin.P2, 1)
                    break;
                }
                while (pins.digitalReadPin(DigitalPin.P0) == 0) {
                    if (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
                        while (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
                            pins.digitalWritePin(DigitalPin.P2, 1)
                        }
                        break;
                    }
                    if (control.millis() >= start_mls + timeout) {
                        timed_out = true
                    }
                    if (timed_out) {
                        pins.digitalWritePin(DigitalPin.P2, 1)
                        break;
                    }
                }
                if (pins.digitalReadPin(DigitalPin.P1) == 1) {
                    data = "" + data + "1"
                } else {
                    data = "" + data + "0"
                }
                pins.digitalWritePin(DigitalPin.P2, 1)
                while (pins.digitalReadPin(DigitalPin.P0) == 1) {
                    if (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
                        while (input.buttonIsPressed(Button.A) || input.buttonIsPressed(Button.B)) {
                            pins.digitalWritePin(DigitalPin.P2, 1)
                        }
                        break;
                    }
                    if (control.millis() >= start_mls + timeout) {
                        timed_out = true
                    }
                    if (timed_out) {
                        pins.digitalWritePin(DigitalPin.P2, 1)
                        break;
                    }
                }
                pins.digitalWritePin(DigitalPin.P2, 0)
            }
        }
        if (pins.digitalReadPin(DigitalPin.P0) == 0 && !(timed_out)) {
            for (let y2 = 0; y2 <= 24; y2++) {
                for (let x2 = 0; x2 <= 24; x2++) {
                    if (data.charAt(x2 + y2 * 5) == "1") {
                        led.plotBrightness(x2, y2, 255)
                    } else {
                        led.plotBrightness(x2, y2, 0)
                    }
                }
            }
        }
    }
})
