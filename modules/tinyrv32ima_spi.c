#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/platform_device.h>

/* CSR reading/writing */

static inline void csr_set_cs(uint8_t enable)
{
    asm volatile("csrrw x0, 0x180, %0\n" : : "r"(!enable));
}

static int csr_start_transfer(uint8_t tx_data)
{
    uint8_t rx_data;

    // Set tx_data
    asm volatile("csrrw x0, 0x182, %0\n" : : "r"(tx_data));

    // Initiate transfer
    asm volatile("csrrw x0, 0x181, %0\n" : : "r"(1));

    // Get rx_data
    asm volatile("csrr %0,0x183" : "=r"(rx_data));
    return rx_data;
}

/* Chip select*/
static void spi_dummy_set_cs(struct spi_device *spi, bool enable)
{
    csr_set_cs(enable);
}

/* Single transfer */
static int spi_dummy_transfer_one(struct spi_master *master,
                                  struct spi_device *spi,
                                  struct spi_transfer *xfer)
{
    uint8_t tx_data;
    uint8_t rx_data;

    if (xfer->len)
    {
        for (int i = 0; i < xfer->len; i++)
        {
            if (xfer->tx_buf)
                tx_data = ((uint8_t *)(xfer->tx_buf))[i];
            else
                tx_data = 0;

            rx_data = csr_start_transfer(tx_data);

            if (xfer->rx_buf)
                ((uint8_t *)(xfer->rx_buf))[i] = rx_data;
        }
    }
    spi_finalize_current_transfer(master);
    return 0;
}

/* Device setup */
static int spi_dummy_setup(struct spi_device *spi)
{
    dev_info(&spi->dev, "Setup device: mode 0x%x, %d bits, %d Hz max\n",
             spi->mode, spi->bits_per_word, spi->max_speed_hz);
    return 0;
}

/* Probe: called when DT node matches */
static int spi_dummy_probe(struct platform_device *pdev)
{
    struct spi_master *master;
    int ret;

    master = devm_spi_alloc_master(&pdev->dev, 0);
    if (!master)
        return -ENOMEM;

    master->dev.of_node = pdev->dev.of_node;
    master->setup = spi_dummy_setup;
    master->transfer_one = spi_dummy_transfer_one;
    master->set_cs = spi_dummy_set_cs;

    ret = devm_spi_register_master(&pdev->dev, master);
    if (ret)
    {
        dev_err(&pdev->dev, "Error registering bus (bus %d)\n",
                master->bus_num);
        return ret;
    }

    dev_info(&pdev->dev, "tiny-rv32ima SPI master registered (bus %d)\n",
             master->bus_num);
    return 0;
}

/* DT match table */
static const struct of_device_id spi_dummy_of_match[] = {
    {.compatible = "tvlad1234,spi-tiny-rv32ima"},
    {}};
MODULE_DEVICE_TABLE(of, spi_dummy_of_match);

static struct platform_driver spi_dummy_driver = {
    .driver = {
        .name = "spi-tinyrv32ima-master",
        .of_match_table = spi_dummy_of_match,
    },
    .probe = spi_dummy_probe,
};

module_platform_driver(spi_dummy_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tvlad1234");
MODULE_DESCRIPTION("tiny-rv32ima SPI driver");
