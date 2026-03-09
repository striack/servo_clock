#!/usr/bin/env bash

# Board configuration
FQBN="arduino:avr:uno"

# Find connected Arduino
PORT=$(arduino-cli board list | awk '/arduino:avr:uno/ {print $1}')

if [ -z "$PORT" ]; then
  echo "❌ No Arduino Uno found"
  exit 1
fi

echo "Using port: $PORT"

echo "🔨 Compiling..."
arduino-cli compile --fqbn $FQBN .

if [ $? -ne 0 ]; then
  echo "❌ Compilation failed"
  exit 1
fi

echo "⬆ Uploading..."
arduino-cli upload -p $PORT --fqbn $FQBN .

echo "✅ Done"
