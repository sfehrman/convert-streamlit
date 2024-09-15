import streamlit as st

FACTOR: str = "factor"
FORMAT_IMPERIAL: str = "format_imperial"
FORMAT_METRIC: str = "format_metric"
LATEX_IMPERIAL: str = "latex_imperial"
LATEX_METRIC: str = "latex_metric"

UNIT_ACCELERATION: str = "Acceleration"
UNIT_AREA: str = "Area"
UNIT_DENSITY: str = "Density"
UNIT_ENERGY: str = "Energy"
UNIT_LENGTH: str = "Length"
UNIT_MASS: str = "Mass"
UNIT_POWER: str = "Power"
UNIT_PRESSURE: str = "Pressure"
UNIT_SPEED: str = "Speed"
UNIT_TEMPERATURE: str = "Temperature"
UNIT_VOLUME: str = "Volume"

MODE_M2I: str = "Metric to Imperial"
MODE_I2M: str = "Imperial to Metric"

unit_types = [
    UNIT_ACCELERATION,
    UNIT_AREA,
    UNIT_DENSITY,
    UNIT_ENERGY,
    UNIT_LENGTH, 
    UNIT_MASS,
    UNIT_POWER,
    UNIT_PRESSURE,
    UNIT_SPEED,
    UNIT_TEMPERATURE, 
    UNIT_VOLUME
]

units = {
    UNIT_ACCELERATION: [
        {
            FORMAT_METRIC: "m/sec^2", 
            FORMAT_IMPERIAL: "ft/sec^2",
            LATEX_METRIC: r'''\frac{meter}{second^2}''',
            LATEX_IMPERIAL: r'''\frac{foot}{second^2}''',
            FACTOR: 3.28084
        },
        {
            FORMAT_METRIC: "m/sec^2", 
            FORMAT_IMPERIAL: "in/sec^2", 
            LATEX_METRIC: r'''\frac{meter}{second^2}''',
            LATEX_IMPERIAL: r'''\frac{inch}{second^2}''',
            FACTOR: 39.3701
        }
    ],
    UNIT_AREA: [
        {
            FORMAT_METRIC: "cm^2", 
            FORMAT_IMPERIAL: "in^2",
            LATEX_METRIC: r'''{centimeter^2}''',
            LATEX_IMPERIAL: r'''{inch^2}''',
            FACTOR: 0.155
        },
        {
            FORMAT_METRIC: "m^2", 
            FORMAT_IMPERIAL: "yd^2",
            LATEX_METRIC: r'''{meter^2}''',
            LATEX_IMPERIAL: r'''{yard^2}''',
            FACTOR: 1.19599
        },
        {
            FORMAT_METRIC: "km^2", 
            FORMAT_IMPERIAL: "mi^2",
            LATEX_METRIC: r'''{kilometers^2}''',
            LATEX_IMPERIAL: r'''{miles^2}''',
            FACTOR: 0.386102
        }
   ],
    UNIT_DENSITY: [
        {
            FORMAT_METRIC: "g/cm^3", 
            FORMAT_IMPERIAL: "lb/in^3",
            LATEX_METRIC: r'''\frac{grams}{centimeter^3}''',
            LATEX_IMPERIAL: r'''\frac{pounds}{inch^3}''',
            FACTOR: 0.0361273
        },
        {
            FORMAT_METRIC: "g/cm^3", 
            FORMAT_IMPERIAL: "lb/ft^3",
            LATEX_METRIC: r'''\frac{grams}{centimeter^3}''',
            LATEX_IMPERIAL: r'''\frac{pounds}{foot^3}''',
            FACTOR: 62.4279737
        },
        {
            FORMAT_METRIC: "kg/m^3", 
            FORMAT_IMPERIAL: "lb/ft^3",
            LATEX_METRIC: r'''\frac{kilograms}{meter^3}''',
            LATEX_IMPERIAL: r'''\frac{pounds}{foot^3}''',
            FACTOR: 0.0624279
        },
    ],
    UNIT_ENERGY: [],
    UNIT_LENGTH: [],
    UNIT_MASS: [],
    UNIT_POWER: [],
    UNIT_PRESSURE: [],
    UNIT_SPEED: [],
    UNIT_TEMPERATURE: [],
    UNIT_VOLUME: []
}

_mode: str = MODE_I2M
_controls, _output = st.columns([1,1])

if 'output_text' not in st.session_state:
    st.session_state.output_text = ""

def append_to_output(text: str) -> None:
    st.session_state.output_text += f"{text}\n\n"
    return

def home() -> None:
    global _mode

    with st.sidebar:
        conversion = st.radio("Select Unit", unit_types)

    with _controls:
        st.subheader("Convert",divider=True)

        _mode = st.radio("Select mode", [MODE_I2M, MODE_M2I])

        if conversion == UNIT_ACCELERATION:
            display(UNIT_ACCELERATION)
        elif conversion == UNIT_AREA:
            display(UNIT_AREA)
        elif conversion == UNIT_DENSITY:
            display(UNIT_DENSITY)
        elif conversion == UNIT_ENERGY:
            energy(UNIT_ENERGY)
        elif conversion == UNIT_LENGTH:
            length(UNIT_LENGTH)
        elif conversion == UNIT_MASS:
            mass(UNIT_MASS)
        elif conversion == UNIT_POWER:
            power(UNIT_POWER)
        elif conversion == UNIT_PRESSURE:
            pressure(UNIT_PRESSURE)
        elif conversion == UNIT_SPEED:
            speed(UNIT_SPEED)
        elif conversion == UNIT_TEMPERATURE:
            temperature(UNIT_TEMPERATURE)
        elif conversion == UNIT_VOLUME:
            volume(UNIT_VOLUME)

    with _output:
        st.text_area("",
                     value=st.session_state.output_text,
                     height=400)
        if st.button("Clear Output"):
            st.session_state.output_text = ""

    return

def display(unit: str) -> None:
    st.subheader(f"{unit}")

    conversions = units[unit]

    label_to_conversion = {}
    options = []

    for conversion in conversions:
        if _mode == MODE_I2M:
            label = f"{conversion[FORMAT_IMPERIAL]} -> {conversion[FORMAT_METRIC]}"
        else:    
            label = f"{conversion[FORMAT_METRIC]} -> {conversion[FORMAT_IMPERIAL]}"
        
        options.append(label)
        label_to_conversion[label] = conversion

    label = st.selectbox("", 
                          index=None,
                          placeholder="Select conversion",
                          options=options)
    
    if label is not None:
        conversion = label_to_conversion[label]

        input_value, input_latex = st.columns(2)
        output_value, output_latex = st.columns(2)

        if _mode == MODE_I2M:
            with input_value:
                value = st.number_input("",step=0.1)

            with input_latex:
                st.latex(conversion[LATEX_IMPERIAL])
            
            result = value / conversion[FACTOR]

            with output_value:
                st.write(f"{result}")
            
            with output_latex:
                st.latex(conversion[LATEX_METRIC])

            if value != 0.0:
                append_to_output(f"{value:.4f} {conversion[FORMAT_IMPERIAL]}\n{result:.4f} {conversion[FORMAT_METRIC]}")

        else:
            with input_value:
                value = st.number_input("")

            with input_latex:
                st.latex(conversion[LATEX_METRIC])
            
            result = value * conversion[FACTOR]

            with output_value:
                st.write(f"{result}")

            with output_latex:         
                st.latex(conversion[LATEX_IMPERIAL])

            if value != 0.0:
                append_to_output(f"{value:.4f} {conversion[FORMAT_METRIC]}\n{result:.4f} {conversion[FORMAT_IMPERIAL]}")

    return

def energy(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def length(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def mass(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def power(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def pressure(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def speed(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def temperature(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

def volume(unit: str) -> None:
    st.write(f"{unit} conversion")
    return

if __name__ == "__main__":
    home()
