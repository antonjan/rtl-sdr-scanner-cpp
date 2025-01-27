#include <config.h>
#include <radio/help_structures.h>
#include <radio/sdr_device.h>

typedef struct rtlsdr_dev rtlsdr_dev_t;

class RtlSdrDevice : public SdrDevice {
 public:
  RtlSdrDevice(const Config& config, const std::string& serial);
  ~RtlSdrDevice() override;

  void startStream(const FrequencyRange& frequencyRange, Callback&& callback) override;
  std::vector<uint8_t> readData(const FrequencyRange& frequencyRange) override;
  std::string name() const override;
  int32_t offset() const override;
  static std::vector<std::string> listDevices();

 private:
  void open();
  void close();
  bool isSamplesOk(uint8_t* buf, uint32_t len);
  void setupDevice(const FrequencyRange& frequencyRange);

  const Config& m_config;
  const std::string m_serial;
  const int m_deviceIndex;
  rtlsdr_dev_t* m_device;
  Frequency m_lastBandwidth;
  std::vector<uint8_t> m_rawBuffer;
};
