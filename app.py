"""
Unit Converter
Copyright (c) 2024, Scott Fehrman, All Rights Reserved.
"""
import streamlit as st

FORMAT_IMPERIAL: str = "format_imperial"
FORMAT_METRIC: str = "format_metric"
LATEX_IMPERIAL: str = "latex_imperial"
LATEX_METRIC: str = "latex_metric"
LAMBDA_TO_IMPERIAL: str = "lambda_to_imperial"
LAMBDA_TO_METRIC: str = "lambda_to_metric"

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
            FORMAT_METRIC: "meters/sec^2", 
            FORMAT_IMPERIAL: "feet/sec^2",
            LATEX_METRIC: r'''\frac{meters}{second^2}''',
            LATEX_IMPERIAL: r'''\frac{feet}{second^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 3.28084),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 3.28084)
        },
        {
            FORMAT_METRIC: "meters/sec^2", 
            FORMAT_IMPERIAL: "inches/sec^2", 
            LATEX_METRIC: r'''\frac{meters}{second^2}''',
            LATEX_IMPERIAL: r'''\frac{inches}{second^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 39.3701),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 39.3701)
        }
    ],
    UNIT_AREA: [
        {
            FORMAT_METRIC: "sqaure cm", 
            FORMAT_IMPERIAL: "sqaure in",
            LATEX_METRIC: r'''{centimeters^2}''',
            LATEX_IMPERIAL: r'''{inches^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.155),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.155)
        },
        {
            FORMAT_METRIC: "square meters", 
            FORMAT_IMPERIAL: "square yards",
            LATEX_METRIC: r'''{meters^2}''',
            LATEX_IMPERIAL: r'''{yards^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 1.19599),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 1.19599)
        },
        {
            FORMAT_METRIC: "square km", 
            FORMAT_IMPERIAL: "square miles",
            LATEX_METRIC: r'''{kilometers^2}''',
            LATEX_IMPERIAL: r'''{miles^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.386102),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.386102)
        }
   ],
    UNIT_DENSITY: [
        {
            FORMAT_METRIC: "grams/cm^3", 
            FORMAT_IMPERIAL: "lbs/in^3",
            LATEX_METRIC: r'''\frac{grams}{centimeter^3}''',
            LATEX_IMPERIAL: r'''\frac{pounds}{inch^3}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.0361273),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.0361273)
        },
        {
            FORMAT_METRIC: "grams/cm^3", 
            FORMAT_IMPERIAL: "lbs/ft^3",
            LATEX_METRIC: r'''\frac{grams}{centimeter^3}''',
            LATEX_IMPERIAL: r'''\frac{pounds}{foot^3}''',
            LAMBDA_TO_METRIC: lambda x: (x * 62.4279737),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 62.4279737)
        },
        {
            FORMAT_METRIC: "kg/meter^3", 
            FORMAT_IMPERIAL: "lb/foot^3",
            LATEX_METRIC: r'''\frac{kilograms}{meter^3}''',
            LATEX_IMPERIAL: r'''\frac{pounds}{foot^3}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.0624279),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.0624279)
        },
    ],
    UNIT_ENERGY: [
        {
            FORMAT_METRIC: "BTUs",
            FORMAT_IMPERIAL: "foot-lbs",
            LATEX_METRIC: r'''BTUs''',
            LATEX_IMPERIAL: r'''foot-pounds''',
            LAMBDA_TO_METRIC: lambda x: (x * 778.1692972),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 778.1692972)
        }
    ],
    UNIT_LENGTH: [
        {
            FORMAT_METRIC: "millimeters",
            FORMAT_IMPERIAL: "inches",
            LATEX_METRIC: r'''millimeters''',
            LATEX_IMPERIAL: r'''inches''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.0393701),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.0393701)
        },
        {
            FORMAT_METRIC: "meters",
            FORMAT_IMPERIAL: "feet",
            LATEX_METRIC: r'''meters''',
            LATEX_IMPERIAL: r'''feet''',
            LAMBDA_TO_METRIC: lambda x: (x * 3.28084),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 3.28084)
        },
        {
            FORMAT_METRIC: "kilometers",
            FORMAT_IMPERIAL: "miles",
            LATEX_METRIC: r'''kilometers''',
            LATEX_IMPERIAL: r'''miles''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.621371),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.621371)
        }
    ],
    UNIT_MASS: [
        {
            FORMAT_METRIC: "grams",
            FORMAT_IMPERIAL: "ounces",
            LATEX_METRIC: r'''grams''',
            LATEX_IMPERIAL: r'''ounces''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.035274),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.035274)
        },
        {
            FORMAT_METRIC: "grams",
            FORMAT_IMPERIAL: "pounds",
            LATEX_METRIC: r'''grams''',
            LATEX_IMPERIAL: r'''pounds''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.00220462),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.00220462)
        },
        {
            FORMAT_METRIC: "kilograms",
            FORMAT_IMPERIAL: "pounds",
            LATEX_METRIC: r'''kilograms''',
            LATEX_IMPERIAL: r'''pounds''',
            LAMBDA_TO_METRIC: lambda x: (x * 2.20462),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 2.20462)
        }
    ],
    UNIT_POWER: [
        {
            FORMAT_METRIC: "BTUs/hr",
            FORMAT_IMPERIAL: "ft-lbs/sec",
            LATEX_METRIC: r'''\frac{BTUs}{hour}''',
            LATEX_IMPERIAL: r'''\frac{foot-pounds}{second}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.216158),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.216158)
        }
    ],
    UNIT_PRESSURE: [
        {
            FORMAT_METRIC: "N/m^2",
            FORMAT_IMPERIAL: "psi",
            LATEX_METRIC: r'''\frac{Newton}{meter^2}=Pa''',
            LATEX_IMPERIAL: r'''\frac{pounds}{inch^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.000145038),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.000145038)
        },
        {
            FORMAT_METRIC: "N/mm^2",
            FORMAT_IMPERIAL: "psi",
            LATEX_METRIC: r'''\frac{Newton}{millimeter^2}=MPa''',
            LATEX_IMPERIAL: r'''\frac{pounds}{inch^2}''',
            LAMBDA_TO_METRIC: lambda x: (x * 145.038),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 145.038)
        }
    ],
    UNIT_SPEED: [
        {
            FORMAT_METRIC: "meters/sec",
            FORMAT_IMPERIAL: "feet/sec",
            LATEX_METRIC: r'''\frac{meters}{second}''',
            LATEX_IMPERIAL: r'''\frac{feet}{second}''',
            LAMBDA_TO_METRIC: lambda x: (x * 3.28084),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 3.28084)
        },
        {
            FORMAT_METRIC: "kilometers/hour",
            FORMAT_IMPERIAL: "miles/hour",
            LATEX_METRIC: r'''\frac{kilometers}{hour}''',
            LATEX_IMPERIAL: r'''\frac{miles}{hour}''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.6213712),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.6213712)
        }
    ],
    UNIT_TEMPERATURE: [
        {
            FORMAT_METRIC: "°C",
            FORMAT_IMPERIAL: "°F",
            LATEX_METRIC: r'''Celsius''',
            LATEX_IMPERIAL: r'''Fahrenheit''',
            LAMBDA_TO_METRIC: lambda x: ((x - 32) * 5/9),
            LAMBDA_TO_IMPERIAL: lambda x: ((x * 9/5) + 32)
        }
    ],
    UNIT_VOLUME: [
        {
            FORMAT_METRIC: "milliliters",
            FORMAT_IMPERIAL: "fluid ounces",
            LATEX_METRIC: r'''milliliters''',
            LATEX_IMPERIAL: r'''{fluid}\:{ounces}''',
            LAMBDA_TO_METRIC: lambda x: (x * 29.57353),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 29.57353)
        },
        {
            FORMAT_METRIC: "liters",
            FORMAT_IMPERIAL: "cubic inches",
            LATEX_METRIC: r'''liters''',
            LATEX_IMPERIAL: r'''inches^3''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.0163871),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.0163871)
        },
        {
            FORMAT_METRIC: "liters",
            FORMAT_IMPERIAL: "gallons",
            LATEX_METRIC: r'''liters''',
            LATEX_IMPERIAL: r'''gallons''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.264172),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.264172)
        },
        {
            FORMAT_METRIC: "liters",
            FORMAT_IMPERIAL: "cubic feet",
            LATEX_METRIC: r'''liters''',
            LATEX_IMPERIAL: r'''feet^3''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.035315),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.035315)
        },
        {
            FORMAT_METRIC: "cubic meters",
            FORMAT_IMPERIAL: "cubic feet",
            LATEX_METRIC: r'''meters^3''',
            LATEX_IMPERIAL: r'''feet^3''',
            LAMBDA_TO_METRIC: lambda x: (x * 35.31467),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 35.31467)
        },
        {
            FORMAT_METRIC: "cubic meters",
            FORMAT_IMPERIAL: "gallons",
            LATEX_METRIC: r'''meters^3''',
            LATEX_IMPERIAL: r'''gallons''',
            LAMBDA_TO_METRIC: lambda x: (x * 264.172),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 264.172)
        },
        {
            FORMAT_METRIC: "cubic cm",
            FORMAT_IMPERIAL: "cubic in",
            LATEX_METRIC: r'''centimeters^3''',
            LATEX_IMPERIAL: r'''inches^3''',
            LAMBDA_TO_METRIC: lambda x: (x * 0.0163870),
            LAMBDA_TO_IMPERIAL: lambda x: (x / 0.0163870)
        }
    ]
}

st.set_page_config(page_title="Unit Converter", 
                   page_icon="📏",
                   layout="wide")

_mode: str = MODE_I2M
_controls, _output = st.columns([1,1])

if 'output_text' not in st.session_state:
    st.session_state.output_text = ""

def append_to_output(text: str) -> None:
    st.session_state.output_text += f"{text}\n"
    return

def home() -> None:
    global _mode

    with st.sidebar:
        conversion = st.radio("Select Unit", unit_types)

    with _controls:
        st.subheader("Convert",divider=True)

        _mode = st.radio("Select mode", [MODE_I2M, MODE_M2I])

        display(conversion)

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
            
            result = conversion[LAMBDA_TO_METRIC](value)

            with output_value:
                st.write(f"{result}")
            
            with output_latex:
                st.latex(conversion[LATEX_METRIC])

            if value != 0.0:
                append_to_output(f"{value:.4f} {conversion[FORMAT_IMPERIAL]} = {result:.4f} {conversion[FORMAT_METRIC]}")

        else:
            with input_value:
                value = st.number_input("")

            with input_latex:
                st.latex(conversion[LATEX_METRIC])
            
            result = conversion[LAMBDA_TO_IMPERIAL](value)

            with output_value:
                st.write(f"{result}")

            with output_latex:         
                st.latex(conversion[LATEX_IMPERIAL])

            if value != 0.0:
                append_to_output(f"{value:.4f} {conversion[FORMAT_METRIC]} = {result:.4f} {conversion[FORMAT_IMPERIAL]}")

    return

if __name__ == "__main__":
    home()
