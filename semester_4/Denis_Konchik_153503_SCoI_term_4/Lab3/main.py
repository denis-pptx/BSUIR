from serializer_Konchik import SerializerFactory
import argparse
import configparser


def parse_config_file(config_file):
    config = configparser.ConfigParser()
    config.read(config_file)

    if 'config' in config:
        config_section = config['config']
        if all(param in config_section
               for param in ['source_file', 'source_format', 'destination_file', 'destination_format']):
            return (config_section['source_file'], config_section['source_format'],
                    config_section['destination_file'], config_section['destination_format'])

    return None


def parse_cli():
    parser = argparse.ArgumentParser(description='JSON / XML serializer')
    parser.add_argument('source_file', type=str, help='Path to source file')
    parser.add_argument('source_format', type=str, choices=['json', 'xml'], help='Format of source file')
    parser.add_argument('destination_file', type=str, help='Path to destination file')
    parser.add_argument('destination_format', type=str, choices=['json', 'xml'], help='Format of destination file')
    args = parser.parse_args()

    return args.source_file, args.source_format, args.destination_file, args.destination_format


def main():
    config_file = 'config.ini'
    config_values = parse_config_file(config_file)

    source_file, source_format, destination_file, destination_format = config_values if config_values else parse_cli()

    source_serializer = SerializerFactory.create(source_format)
    destination_serializer = SerializerFactory.create(destination_format)

    with open(source_file, "r") as file:
        obj = source_serializer.load(file)

    with open(destination_file, "w") as file:
        destination_serializer.dump(obj, file)


if __name__ == '__main__':
    main()
